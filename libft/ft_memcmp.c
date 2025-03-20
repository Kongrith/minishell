/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:52:36 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/26 16:38:49 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t count)
{
	const unsigned char	*s1 = (const unsigned char*) str1;
	const unsigned char	*s2 = (const unsigned char*) str2;

	while (count-- > 0)
	{
		if (*s1++ != *s2++)
			return (s1[-1] - s2[-1]);
	}
	return (0);
}
