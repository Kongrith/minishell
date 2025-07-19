/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:56:59 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 09:42:28 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_sh *sh, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "env") == 0)
		sh->status = b_env(sh, cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		b_exit(sh, cmd);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		sh->status = b_echo(sh, cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		sh->status = b_pwd(sh);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		sh->status = b_cd(sh, cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		sh->status = b_unset(sh, cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		sh->status = b_export(sh, cmd);
}
