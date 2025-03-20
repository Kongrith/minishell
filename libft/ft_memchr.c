/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:38:13 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/28 14:41:00 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *src_void, int c, size_t length)
{
	const unsigned char	*src = (const unsigned char *) src_void;

	while (length-- > 0)
	{
		if ((unsigned char) *src == (unsigned char) c)
			return ((void *) src);
		src++;
	}
	return (NULL);
}
