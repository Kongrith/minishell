/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:44:59 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 10:02:29 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_compare_args(t_sh *sh, t_cmd *cmd, int i, bool *new_line)
{
	char	*ptr;

	if (ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		ptr = cmd->args[i];
		ptr++;
		while (*ptr)
		{
			if (*ptr != 'n')
				return (i);
			ptr++;
		}
		*new_line = false;
		i++;
	}
	else if (ft_strcmp(cmd->args[i], "$?") == 0)
	{
		ft_printf("%d", sh->status);
		i++;
	}
	return (i);
}

int	b_echo(t_sh *sh, t_cmd *cmd)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	if (!cmd->args[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	i = echo_compare_args(sh, cmd, i, &new_line);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
