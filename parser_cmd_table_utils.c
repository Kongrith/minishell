/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_table_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 05:54:46 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/16 13:07:45 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_arg(t_sh *sh, t_cmd *new_node, char *arg)
{
	char	*dequote_arg;

	dequote_arg = dequote(sh, arg);
	if (dequote_arg == NULL)
		return ;
	new_node->args[sh->cmd_indx] = ft_strdup(dequote_arg);
	if (dequote_arg)
		free(dequote_arg);
	sh->cmd_indx += 1;
}

void	assign_cmd(t_sh *sh, t_cmd *new_node, char *arg)
{
	char	*dequote_arg;

	dequote_arg = dequote(sh, arg);
	if (dequote_arg == NULL)
		return ;
	if (sh->cmd_indx == 0)
	{
		new_node->args[0] = ft_strdup(dequote_arg);
		new_node->cmd = ft_strdup(dequote_arg);
		new_node->builtin = eval_builtin(new_node->cmd);
		sh->cmd_indx += 1;
		sh->cmd_flag = 0;
	}
	if (dequote_arg)
		free(dequote_arg);
}

bool	eval_builtin(char *cmd)
{
	if (check_cmd(cmd, "env") || check_cmd(cmd, "exit") || \
check_cmd(cmd, "echo") || check_cmd(cmd, "pwd") || \
check_cmd(cmd, "cd") || check_cmd(cmd, "unset") || check_cmd(cmd, "export"))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool	eval_operator(char *cmd)
{
	if (eval_redi(cmd) || check_cmd(cmd, "|") || check_cmd(cmd, "||") || \
check_cmd(cmd, "&") || check_cmd(cmd, "&&"))
		return (true);
	else
		return (false);
}

bool	eval_cmd(char *cmd)
{
	if (eval_builtin(cmd) || (!eval_operator(cmd)))
		return (true);
	else
		return (false);
}
