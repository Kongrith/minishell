/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:28:07 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/13 11:23:08 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	validate_base(char *base)
{
	int			i;
	int			j;
	const int	len = ft_strlen(base);

	if (len <= 1)
		return (0);
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (base[i] == base[j])
			{
				return (0);
			}
			j++;
		}
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	return (len);
}

static int	buf_len(long lnbr, char *base)
{
	int			len;
	const int	len_base = ft_strlen(base);

	len = 1;
	if (lnbr < 0)
	{
		len++;
		lnbr = -lnbr;
	}
	while (lnbr >= len_base)
	{
		lnbr /= len_base;
		len++;
	}
	return (len);
}

char	*ft_putnbr_base(long lnbr, char *base)
{
	const int	len_base = validate_base(base);
	int			i;
	char		*buf;

	i = buf_len(lnbr, base);
	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (NULL);
	if (len_base)
	{
		if (lnbr < 0)
		{
			buf[0] = '-';
			lnbr = -lnbr;
		}
		buf[i--] = '\0';
		while (len_base <= lnbr)
		{
			buf[i--] = base[lnbr % len_base];
			lnbr /= len_base;
		}
		buf[i] = base[lnbr % len_base];
		return (buf);
	}
	return (NULL);
}
