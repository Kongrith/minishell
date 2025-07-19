/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:28:38 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/02 15:46:31 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_flags(t_rd *rd)
{
	int	flags;

	if (rd->type == RD_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (flags);
}

int	rd_output_file(t_sh *sh, t_cmd *cmd, t_rd *rd)
{
	int	flags;
	int	fd;

	flags = set_flags(rd);
	fd = open(rd->file_name, flags, 0644);
	if (fd == -1)
	{
		print_shell_error(rd->file_name, strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
		sh->status = 1;
		return (1);
	}
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (close(cmd->fd_out), 1);
	return (0);
}
