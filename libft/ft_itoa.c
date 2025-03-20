/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:01:32 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/30 11:14:04 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	buf_len(long int lnbr)
{
	int	len;

	len = 1;
	if (lnbr < 0)
	{
		len++;
		lnbr = -lnbr;
	}
	while (lnbr >= 10)
	{
		lnbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*buf;
	int			i;
	long int	lnbr;

	i = buf_len(n);
	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (NULL);
	lnbr = n;
	if (lnbr < 0)
	{
		buf[0] = '-';
		lnbr = -lnbr;
	}
	buf[i--] = '\0';
	while (lnbr >= 10)
	{
		buf[i--] = (lnbr % 10) + '0';
		lnbr /= 10;
	}
	buf[i] = (lnbr % 10) + '0';
	return (buf);
}
