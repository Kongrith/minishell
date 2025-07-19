/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:40:03 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/02 15:30:02 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_rd_exit(t_rd *rd, int *fd)
{
	size_t	len;
	ssize_t	bytes_written;

	close(fd[0]);
	len = ft_strlen(rd->content);
	bytes_written = write(fd[1], rd->content, len);
	close(fd[1]);
	if (bytes_written == -1)
		exit(1);
	exit(0);
}

int	parent_rd_exit(t_sh *sh, t_cmd *cmd, pid_t pid, int *fd)
{
	int	std_in;
	int	status;

	close(fd[1]);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1)
		return (close(fd[0]), fd[0] = -1, 1);
	cmd->fd_in = fd[0];
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (close(cmd->fd_in), cmd->fd_in = -1, close(std_in), 1);
	waitpid(pid, &status, 0);
	close(fd[0]);
	close(std_in);
	if (WIFEXITED(status))
		sh->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->status = 128 + WTERMSIG(status);
	return (0);
}

int	rd_input_file(t_sh *sh, t_cmd *cmd, t_rd *rd)
{
	int	fd;

	fd = open(rd->file_name, O_RDONLY);
	if (fd == -1)
	{
		print_shell_error(rd->file_name, strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
		sh->status = 1;
		return (1);
	}
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (close(cmd->fd_in), cmd->fd_in = -1, 1);
	return (0);
}

int	rd_heredoc(t_sh *sh, t_cmd *cmd, t_rd *rd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror_exit(SHELL_ERROR_PROMPT, 1), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]),
			perror_exit(SHELL_ERROR_PROMPT, 1), 1);
	if (pid == 0)
		child_rd_exit(rd, fd);
	else
		return (parent_rd_exit(sh, cmd, pid, fd));
	return (0);
}
