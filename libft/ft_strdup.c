/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:16:10 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/10 14:12:56 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char			*dupstring;
	const size_t	src_len = ft_strlen(src);

	if (!src)
		return (NULL);
	dupstring = malloc(sizeof(char) * (src_len + 1));
	if (!dupstring)
		return (NULL);
	dupstring = ft_memcpy(dupstring, src, src_len + 1);
	return (dupstring);
}
