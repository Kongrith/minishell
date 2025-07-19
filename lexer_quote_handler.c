/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 03:49:48 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/12 16:58:30 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quotes(char *str, int *pos, char c)
{
	int		i;
	int		start;
	int		end;
	int		len;
	char	*sub;

	start = *pos;
	end = (ft_strchr(str + *pos + 1, c) - (str));
	len = end - start + 1;
	sub = (char *)ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (str[i] != '\0' && i + start <= end)
	{
		sub[i] = str[i + start];
		i++;
	}
	sub[i] = '\0';
	*pos = end;
	return (sub);
}

static char	*lexer_handler(char *str, int *pos)
{
	char	*tmp;

	tmp = NULL;
	if (str[*pos] == '\'' && ft_strchr(str + *pos + 1, '\'') != NULL)
		tmp = handle_quotes(str, pos, '\'');
	else if (str[*pos] == '\"' && ft_strchr(str + *pos + 1, '\"') != NULL)
		tmp = handle_quotes(str, pos, '\"');
	else
		tmp = handle_charactor(str, pos);
	return (tmp);
}

char	*handle_charactor_and_quotes(char *str, int *pos)
{
	char	*token;
	char	*tmp;

	tmp = NULL;
	token = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	token[0] = '\0';
	while (str[*pos] != '\0' && (!ft_isspace(str[*pos]) && \
!is_operator(str[*pos])))
	{
		tmp = lexer_handler(str, pos);
		dynamic_token_size(&token, str, tmp);
		ft_strcat(token, tmp);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		(*pos)++;
	}
	return (token);
}
