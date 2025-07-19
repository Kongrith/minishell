/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:01:16 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/12 16:41:51 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	next_index_from_str(char *str, int offset, char c)
{
	int	index;

	index = (ft_strchr(str + offset + 1, c) - (str));
	return (index);
}

char	*substring_and_remove_quotes(char *str, int *cur, char c)
{
	int		i;
	int		j;
	int		end;
	char	*sub;

	sub = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = *cur;
	j = 0;
	if (str[i] == c)
		i = *cur + 1;
	end = next_index_from_str(str, *cur, c);
	while (str[i] != '\0' && i < end)
		sub[j++] = str[i++];
	sub[j] = '\0';
	*cur = end;
	return (sub);
}

static char	*create_first_segment(char *str, char *sub_str, \
int pos, int cur)
{
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(str) - (cur - pos) + ft_strlen(sub_str);
	new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (pos > 0)
	{
		ft_strncpy(new_str, str, pos);
		new_str[pos] = '\0';
		ft_strcat(new_str, sub_str);
	}
	else
		ft_strcpy(new_str, sub_str);
	return (new_str);
}

char	*insert_expand_string(char *str, char *sub_str, \
int pos, int cur)
{
	char	*new_str;
	char	*aux_str;
	int		rem_len;

	new_str = create_first_segment(str, sub_str, pos, cur);
	if (sub_str)
		free(sub_str);
	rem_len = ft_strlen(str + cur);
	if (cur != (int)ft_strlen(str) && rem_len > 0)
	{
		aux_str = (char *)ft_calloc(rem_len + 1, sizeof(char));
		ft_strncpy(aux_str, str + cur, rem_len);
		aux_str[rem_len] = '\0';
		ft_strcat(new_str, aux_str);
		if (aux_str)
			free(aux_str);
		if (str)
			free(str);
		return (new_str);
	}
	if (str)
		free(str);
	return (new_str);
}
