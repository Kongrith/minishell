/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_char_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:42:55 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/12 17:00:41 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_charactor(char *str, int *pos)
{
	char	*tmp;

	tmp = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	tmp[0] = str[*pos];
	tmp[1] = '\0';
	return (tmp);
}
