/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:52:54 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/14 19:58:26 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Remove the mock stuff when parser is complete.

#include "minishell.h"

/*
bool	check_cmd(char *cmd, char *str)
{
	if (ft_strcmp(cmd, str) == 0)
		return (true);
	return (false);
}
*/

// TODO: This function will be replaced once the parser is ready.
void	mock_exec(t_sh *sh)
{
	sh->cmd_list = mock_cmd(sh->input);
	if (!sh->cmd_list)
		return ;
	if (check_cmd(sh->cmd_list->cmd, "env"))
		sh->status = b_env(sh, &sh->cmd_list[0]);
	else if (check_cmd(sh->cmd_list->cmd, "exit"))
		b_exit(sh, sh->cmd_list);
	else if (check_cmd(sh->cmd_list->cmd, "echo"))
		sh->status = b_echo(sh, &sh->cmd_list[0]);
	else if (check_cmd(sh->cmd_list->cmd, "pwd"))
		sh->status = b_pwd(sh);
	else if (check_cmd(sh->cmd_list->cmd, "cd"))
		sh->status = b_cd(sh, &sh->cmd_list[0]);
	else if (check_cmd(sh->cmd_list->cmd, "unset"))
		sh->status = b_unset(sh, &sh->cmd_list[0]);
	else if (check_cmd(sh->cmd_list->cmd, "export"))
		sh->status = b_export(sh, &sh->cmd_list[0]);
	else
	{
		sh->cmd_list->builtin = false;
		exec_command(sh);
	}
	free_cmd_list(sh);
}
