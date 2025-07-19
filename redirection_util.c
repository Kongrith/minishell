/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:12:20 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/10 22:20:51 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strnlen(const char *s, size_t max_len)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (len < max_len && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strnlen(s, n);
	dup = (char *)malloc((sizeof(char) * len) + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
