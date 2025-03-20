/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:46:59 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/03 18:31:12 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	offset;
	size_t	i;

	offset = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (dest_len < size)
		offset += dest_len;
	else
		offset += size;
	i = 0;
	while (i + offset < (size - 1) && i < src_len)
	{
		dest[offset + i] = src[i];
		i++;
	}
	if (offset < size)
		dest[offset + i] = '\0';
	return (src_len + offset);
}
