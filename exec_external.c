/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:36:56 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/09 15:33:16 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_prog(t_sh *sh, t_cmd *cmd)
{
	char	*cmd_path;
	pid_t	pid;

	if (!cmd->cmd)
		return ;
	cmd_path = check_cmd_path(sh, cmd->cmd);
	if (!cmd_path)
		return ((void)exec_cmd_error(sh, cmd->cmd));
	pid = fork();
	if (pid == -1)
	{
		print_shell_error("fork", strerror(errno));
		sh->status = 1;
	}
	if (pid == 0)
	{
		if (execve(cmd_path, cmd->args, sh->envp) == -1)
			execve_cmd_error(sh, &cmd_path);
	}
	else
	{
		wait_for_child(sh, pid);
		free(cmd_path);
	}
}

void	fork_to_pids(t_sh *sh, int **pipe_fds, pid_t *pids)
{
	int	i;

	i = -1;
	while (++i < sh->cmd_len)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			break ;
		}
		if (pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_piped_commands(sh, pipe_fds, i);
		}
	}
}

int	dup_fd_std(t_sh *sh, int *fd_in, int *fd_out)
{
	*fd_in = dup(STDIN_FILENO);
	*fd_out = dup(STDOUT_FILENO);
	if (*fd_in == -1 || *fd_out == -1)
	{
		if (*fd_in != -1)
		{
			close(*fd_in);
			*fd_in = -1;
		}
		if (*fd_out != -1)
		{
			close(*fd_out);
			*fd_out = -1;
		}
		sh->status = 1;
		return (-1);
	}
	return (1);
}

int	exec_command(t_sh *sh)
{
	int	fd_in;
	int	fd_out;

	if (!sh->cmd_list)
		return (0);
	signal(SIGINT, signal_handler_noninteractive);
	signal(SIGQUIT, SIG_IGN);
	if (dup_fd_std(sh, &fd_in, &fd_out) == -1)
		return (0);
	if (handle_redirections(sh, sh->cmd_list))
	{
		restore_fd_std(&fd_in, &fd_out);
		return (0);
	}
	if (sh->cmd_list->builtin)
		exec_builtin(sh, sh->cmd_list);
	else
		exec_prog(sh, sh->cmd_list);
	restore_fd_std(&fd_in, &fd_out);
	close_redirections(sh->cmd_list);
	return (1);
}

int	exec_commands(t_sh *sh)
{
	int		**pipe_fds;
	pid_t	*pids;

	if (sh->cmd_len == 0)
		return (0);
	if (sh->cmd_len == 1)
		return (exec_command(sh));
	pipe_fds = alloc_pipe_fds(sh);
	pids = alloc_pids(sh);
	open_pipes(sh, pipe_fds);
	fork_to_pids(sh, pipe_fds, pids);
	close_pipes(sh, pipe_fds);
	wait_for_children(sh, pids);
	free_pipe_fds(sh, pipe_fds);
	free(pids);
	return (0);
}
