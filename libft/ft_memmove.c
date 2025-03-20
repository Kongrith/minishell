/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:57:01 by rvesterl          #+#    #+#             */
/*   Updated: 2024/10/07 15:28:33 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	const char	*firsts;
	char		*firstd;
	const char	*lasts;
	char		*lastd;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		firsts = (const char *) src;
		firstd = (char *) dest;
		while (len--)
			*firstd++ = *firsts++;
	}
	else
	{
		lasts = (const char *) src + (len - 1);
		lastd = (char *) dest + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dest);
}
