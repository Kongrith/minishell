/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:15:02 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/09 12:26:38 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*start;

	if ((s1 == NULL) && (s2 == NULL))
		return (NULL);
	start = s1;
	while (*start != '\0')
		start++;
	while (*s2 != '\0')
		*start++ = *s2++;
	*start = '\0';
	return (s1);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ret;

	if (src == NULL)
		return (NULL);
	ret = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ret);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
