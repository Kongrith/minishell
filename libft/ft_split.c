/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:48:46 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/03 14:41:27 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	num_str(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	str_len_chr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		s_len;
	int		i;
	int		pos;

	res = malloc(sizeof(char *) * (num_str(str, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	pos = 0;
	while (str[pos] != '\0')
	{
		while (str[pos] == c)
			pos++;
		if (str[pos] != '\0')
		{
			s_len = str_len_chr(&str[pos], c);
			res[i++] = ft_substr(str, pos, s_len);
			pos += s_len;
		}
	}
	res[i] = NULL;
	return (res);
}
