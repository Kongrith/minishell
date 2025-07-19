/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:31:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/10 10:32:58 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_rd_content(t_rd *rd)
{
	rd->content = ft_calloc(1, sizeof(char));
	if (!rd->content)
	{
		print_shell_error(HEREDOC_ORIGIN, ERROR_MEMORY_ALLOCATION);
		return (0);
	}
	return (1);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint_status = 1;
	rl_on_new_line();
	rl_replace_line("\n", 0);
}

int	heredoc_lines(t_sh *sh, t_rd *rd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_sigint_heredoc);
		if (g_sigint_status)
		{
			sh->status = 130;
			g_sigint_status = 0;
			return (0);
		}
		line = readline("> ");
		if (!line)
		{
			delimiter_error(rd->file_name);
			write(1, "\n", 1);
			return (1);
		}
		if (ft_strcmp(line, rd->file_name) == 0)
			return (free(line), 1);
		if (!append_delimiter(rd, line))
			return (free(line), 0);
		free(line);
	}
}

int	heredoc_expand(t_sh *sh, t_rd *rd)
{
	char	*expand;
	char	*temp;

	if (!rd || !rd->content)
		return (0);
	expand = quote_expand(sh, rd->content);
	if (expand)
	{
		free(rd->content);
		temp = ft_strjoin(expand, "\n");
		free(expand);
		rd->content = temp;
		return (1);
	}
	else
	{
		print_shell_error(HEREDOC_ORIGIN, ERROR_EXPAND_HEREDOC);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	heredoc_read(t_sh *sh, t_cmd *cmd, t_rd *rd)
{
	char	*temp;

	if (!rd || !cmd || !cmd->rd_list)
		return (0);
	if (!init_rd_content(rd))
		return (0);
	if (!heredoc_lines(sh, rd))
	{
		free(rd->content);
		rd->content = NULL;
		return (0);
	}
	if (rd->expand == true)
	{
		if (!heredoc_expand(sh, rd))
			return (0);
	}
	else
	{
		temp = ft_strjoin(rd->content, "\n");
		free(rd->content);
		rd->content = temp;
	}
	return (1);
}
