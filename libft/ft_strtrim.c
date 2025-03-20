/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:10:57 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/29 10:44:15 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const size_t	s1_len = ft_strlen(s1);
	size_t			start;
	size_t			end;
	char			*t_str;

	if (s1_len == 0)
		return (ft_strdup(""));
	start = 0;
	end = s1_len - 1;
	while (is_in_set(s1[start], set) && start <= end)
		start++;
	while (is_in_set(s1[end], set) && end >= start)
		end--;
	if (start > end)
		return (ft_strdup(""));
	t_str = ft_calloc(sizeof(char), (end - start + 2));
	if (!t_str)
		return (NULL);
	ft_memcpy(t_str, &s1[start], (end - start + 1));
	return (t_str);
}
