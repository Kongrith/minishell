/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:59:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/28 16:39:56 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_child(t_sh *sh, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->status = 128 + WTERMSIG(status);
	if (status > 128)
		status = status - 128;
	print_signal_error(status);
}

void	wait_for_children(t_sh *sh, pid_t *pids)
{
	int	i;

	i = -1;
	while (++i < sh->cmd_len)
		wait_for_child(sh, pids[i]);
}
