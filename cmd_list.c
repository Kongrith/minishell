/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:54:35 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/09 11:24:46 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds new command to front of list.
void	add_cmd(t_sh *sh, t_cmd *cmd)
{
	if (DEBUG)
		printf("Debug -- Added command '%s'.\n", cmd->cmd);
	cmd->next = sh->cmd_list;
	sh->cmd_list = cmd;
	sh->cmd_len++;
}

// Deletes the last (oldest) command in list and frees its memory.
void	del_last_cmd(t_sh *sh)
{
	t_cmd	*current;
	t_cmd	*previous;

	current = sh->cmd_list;
	previous = NULL;
	while (current)
	{
		if (!current->next)
		{
			if (DEBUG)
				printf("Debug -- Last command '%s' deleted.\n", current->cmd);
			if (previous)
				previous->next = NULL;
			else
				sh->cmd_list = NULL;
			if (current->args)
				free_args(current->args);
			free(current);
			sh->cmd_len--;
			return ;
		}
		previous = current;
		current = current->next;
	}
}
