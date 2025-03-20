/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:23:11 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/03 14:39:15 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == (char) c)
			result = ((char *) str);
		str++;
	}
	if (*str == (char) c)
		result = ((char *) str);
	return (result);
}
