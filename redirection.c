/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:51:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/02 15:27:58 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_single_redirection(t_sh *sh, t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_rd		*rd;

	cmd = cmd_list;
	while (cmd)
	{
		rd = cmd->rd_list;
		while (rd)
		{
			if (cmd->next == NULL && rd->file_name == NULL)
				return (print_syntax_error(sh, ERROR_TOKEN_NEWLINE));
			else if (cmd->next != NULL && rd->file_name == NULL)
				return (print_syntax_error(sh, ERROR_TOKEN_PIPE));
			rd = rd->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	handle_redirection(t_sh *sh, t_cmd *cmd, t_rd *rd)
{
	int	result;

	result = 0;
	if (rd->type == RD_INPUT)
		result = rd_input_file(sh, cmd, rd);
	else if (rd->type == RD_HEREDOC)
		result = rd_heredoc(sh, cmd, rd);
	else if (rd->type == RD_OUTPUT || rd->type == RD_APPEND)
		result = rd_output_file(sh, cmd, rd);
	if (result)
	{
		close_redirections(cmd);
		return (1);
	}
	return (0);
}

int	handle_redirections(t_sh *sh, t_cmd *cmd)
{
	t_rd		*current;
	int			result;

	if (!cmd || !cmd->rd_list)
		return (0);
	current = cmd->rd_list;
	while (current)
	{
		result = handle_redirection(sh, cmd, current);
		if (result == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

void	close_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

void	restore_fd_std(int *fd_in, int *fd_out)
{
	if (dup2(*fd_in, STDIN_FILENO) == -1)
		perror("STDIN");
	if (*fd_in != -1)
		close(*fd_in);
	*fd_in = -1;
	if (dup2(*fd_out, STDOUT_FILENO) == -1)
		perror("STDOUT");
	if (*fd_out != -1)
		close(*fd_out);
	*fd_out = -1;
}
