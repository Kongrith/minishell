/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:29:22 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/16 13:39:18 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_is_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || \
		c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

size_t	ft_conv_pos(const char *str, size_t pos)
{
	if (str[pos] == '%')
	{
		pos++;
		while (str[pos] != '\0')
		{
			if (ft_is_conv(str[pos]))
			{
				pos++;
				break ;
			}
			pos++;
		}
	}
	else
	{
		while (str[pos] != '%' && str[pos] != '\0')
			pos++;
	}
	return (pos);
}
