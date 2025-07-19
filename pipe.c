/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:45:49 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/09 15:36:55 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe_prog(t_sh *sh, t_cmd *cmd, char *cmd_path)
{
	if (handle_redirections(sh, cmd))
	{
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, cmd->args, sh->envp) == -1)
	{
		print_shell_error(cmd->args[0], strerror(errno));
		sh->status = 1;
		free(cmd_path);
		exit(errno);
	}
}

void	close_pipes(t_sh *sh, int **pipe_fds)
{
	int	i;

	i = -1;
	while (++i < sh->cmd_len - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
	}
}

void	open_pipes(t_sh *sh, int **pipe_fds)
{
	int	i;

	i = -1;
	while (++i < sh->cmd_len - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			free_pipe_fds(sh, pipe_fds);
			perror_exit("pipe", 1);
		}
	}
}

void	exec_piped_command(t_sh *sh, t_cmd *cmd)
{
	char	*cmd_path;

	if (handle_redirections(sh, cmd) != 0)
		exit (1);
	if (cmd->builtin)
	{
		exec_builtin(sh, cmd);
		exit(sh->status);
	}
	if (!cmd->args || !cmd->cmd)
		exit(0);
	cmd_path = check_cmd_path(sh, cmd->cmd);
	if (!cmd_path)
		exit(exec_cmd_error(sh, cmd->cmd));
	exec_pipe_prog(sh, cmd, cmd_path);
}

void	exec_piped_commands(t_sh *sh, int **pipe_fds, int i)
{
	t_cmd	*cmd;
	int		j;

	if (i > 0)
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
	if (i < sh->cmd_len - 1)
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	close_pipes(sh, pipe_fds);
	cmd = sh->cmd_list;
	j = 0;
	while (cmd)
	{
		if (j == i)
			exec_piped_command(sh, cmd);
		cmd = cmd->next;
		j++;
	}
}
