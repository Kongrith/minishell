/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:15:53 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/26 14:09:25 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *dest, register int val, register size_t len)
{
	register unsigned char	*ptr;

	ptr = (unsigned char *) dest;
	while (len-- > 0)
		*ptr++ = val;
	return (dest);
}
