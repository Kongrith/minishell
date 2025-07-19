/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 23:16:45 by kkomasat          #+#    #+#             */
/*   Updated: 2025/06/22 23:03:43 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	else
		return (0);
}

char	*handle_operator(char *str, int *pos)
{
	char	*token;

	token = NULL;
	if (str[*pos] == '<' && str[*pos + 1] == '<')
		token = ft_strdup("<<");
	else if (str[*pos] == '>' && str[*pos + 1] == '>')
		token = ft_strdup(">>");
	else if (str[*pos] == '&' && str[*pos + 1] == '&')
		token = ft_strdup("&&");
	else if (str[*pos] == '|' && str[*pos + 1] == '|')
		token = ft_strdup("||");
	else if (str[*pos] == '|')
		token = ft_strdup("|");
	else if (str[*pos] == '<')
		token = ft_strdup("<");
	else if (str[*pos] == '>')
		token = ft_strdup(">");
	else if (str[*pos] == '&')
		token = ft_strdup("&");
	(*pos) += ft_strlen(token);
	return (token);
}
