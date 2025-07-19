/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:10:24 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/04 11:42:54 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_chdir(t_sh *sh, t_cmd *cmd)
{
	t_env	*home;

	if (cmd->args && cmd->args[1])
	{
		if (chdir(cmd->args[1]) == -1)
		{
			print_shell_p_error(cmd->cmd, cmd->args[1]);
			return (1);
		}
	}
	else
	{
		home = get_env_entry(sh->env_list, "HOME");
		if (!home)
			print_shell_error(cmd->cmd, ERROR_HOME_NOT_SET);
		if (chdir(home->value) == -1)
		{
			print_shell_p_error(cmd->cmd, home->value);
			return (1);
		}
	}
	return (0);
}

int	b_cd(t_sh *sh, t_cmd *cmd)
{
	char	*cwd;

	if (cmd->args && cmd->args[1] && cmd->args[2])
	{
		print_shell_error(cmd->cmd, ERROR_TOO_MANY_ARGS);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		print_cwd_error(ERROR_ORIGIN_CHDIR);
	else
		free(cwd);
	if (do_chdir(sh, cmd) != 0)
		return (1);
	if (sh->oldwd)
		free(sh->oldwd);
	if (sh->cwd)
		sh->oldwd = sh->cwd;
	cwd = getcwd(NULL, 0);
	if (cwd)
		sh->cwd = cwd;
	return (0);
}
