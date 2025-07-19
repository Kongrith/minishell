/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:59 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/25 09:31:35 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**alloc_pipe_fds(t_sh *sh)
{
	int		**pipe_fds;
	int		i;

	pipe_fds = ft_calloc(sh->cmd_len - 1, sizeof(int *));
	if (!pipe_fds)
		perror_exit("malloc", EXIT_FAILURE);
	i = -1;
	while (++i < sh->cmd_len - 1)
	{
		pipe_fds[i] = ft_calloc(2, sizeof(int));
		if (!pipe_fds[i])
			perror_exit("malloc", EXIT_FAILURE);
	}
	return (pipe_fds);
}

pid_t	*alloc_pids(t_sh *sh)
{
	int	*pids;

	pids = ft_calloc(sh->cmd_len, sizeof(pid_t));
	if (!pids)
		perror_exit("malloc", EXIT_FAILURE);
	return (pids);
}

void	free_pipe_fds(t_sh *sh, int **pipe_fds)
{
	int	i;

	i = -1;
	while (++i < sh->cmd_len - 1)
		free(pipe_fds[i]);
	free(pipe_fds);
}
