/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:18:17 by rvesterl          #+#    #+#             */
/*   Updated: 2024/10/07 15:29:17 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	if (!dest && !src)
		return (NULL);
	s = (const char *) src;
	d = (char *) dest;
	while (len--)
		*d++ = *s++;
	return (dest);
}
