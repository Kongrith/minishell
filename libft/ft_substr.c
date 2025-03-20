/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:45:39 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/30 14:47:07 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub_str;
	const size_t	s_len = ft_strlen(s);

	if (start > s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	sub_str = ft_calloc(sizeof(char), len + 1);
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, len);
	return (sub_str);
}
