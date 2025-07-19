/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:05:19 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/01 13:53:12 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	walk_space(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\f' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\t' || s[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	i = walk_space(str);
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i++] - '0');
		}
		else
			return (result * sign);
	}
	return (result * sign);
}
