/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 07:34:41 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/29 07:59:28 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	char			*combined_s;

	combined_s = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (!combined_s)
		return (NULL);
	ft_memcpy(&combined_s[0], s1, s1_len);
	ft_memcpy(&combined_s[s1_len], s2, s2_len);
	return (combined_s);
}
