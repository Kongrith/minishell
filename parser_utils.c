/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:44:02 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/16 08:40:21 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	init_parser(t_sh *sh)
{
	sh->file_flag = 0;
	sh->cmd_flag = 1;
	sh->cmd_indx = 0;
	sh->redi_indx = 0;
}

int	count_pointer_to_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}

bool	check_cmd(char *cmd, char *str)
{
	if (ft_strcmp(cmd, str) == 0)
		return (true);
	return (false);
}
