/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_space_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 03:52:05 by kkomasat          #+#    #+#             */
/*   Updated: 2025/06/04 22:42:53 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\a')
		return (1);
	else
		return (0);
}

void	handle_whitespaces(char *str, int *pos)
{
	while (str[*pos] && ft_isspace(str[*pos]))
		(*pos)++;
}
