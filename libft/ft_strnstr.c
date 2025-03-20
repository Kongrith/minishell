/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:57:45 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/28 09:00:09 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	const size_t	str_len = ft_strlen(str);
	const size_t	find_len = ft_strlen(find);
	size_t			i;
	size_t			j;

	if (find_len == 0)
		return ((char *) str);
	if (str_len == 0 || len == 0)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (find[j] == str[i + j] && (i + j) < len)
		{
			if (find[j + 1] == '\0')
				return ((char *) &str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
