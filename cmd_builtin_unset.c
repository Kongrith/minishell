/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:32:13 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/25 09:30:59 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_sh *sh, t_cmd *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (cmd->args[i])
				del_env_entry(sh, cmd->args[i]);
		}
	}
	return (0);
}
