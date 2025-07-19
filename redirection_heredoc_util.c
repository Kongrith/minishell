/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:12:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/10 15:17:58 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(t_sh *sh, const char *name)
{
	t_env	*current;

	if (!name)
		return (NULL);
	current = sh->env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*env_name(const char **input)
{
	const char	*start;
	const char	*end;

	while (**input == '$')
		(*input)++;
	start = *input;
	end = start;
	while (*end && (ft_isalnum(*end) || *end == '_'
			|| *end == '-' || *end == '.'))
		end++;
	if (start == end)
		return (NULL);
	*input = end;
	return (ft_strndup(start, end - start));
}

int	append_delimiter(t_rd *rd, char *line)
{
	char	*temp;
	char	*append;

	if (!rd->content)
		return (0);
	if (rd->content[0] == '\0')
		temp = ft_strdup(line);
	else
	{
		temp = ft_strjoin(rd->content, "\n");
		if (!temp)
			return (print_shell_error(HEREDOC_ORIGIN, ERROR_MEMORY_ALLOCATION),
				0);
		append = ft_strjoin(temp, line);
		free(temp);
		temp = append;
	}
	if (!temp)
		return (print_shell_error(HEREDOC_ORIGIN, ERROR_MEMORY_ALLOCATION), 0);
	free(rd->content);
	rd->content = temp;
	return (1);
}

int	fill_heredoc(t_sh *sh, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	t_rd	*rd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->rd_list)
		{
			rd = cmd->rd_list;
			while (rd)
			{
				if (rd->type == RD_HEREDOC)
				{
					if (!heredoc_read(sh, cmd, rd))
						return (0);
				}
				rd = rd->next;
			}
		}
		cmd = cmd->next;
	}
	return (1);
}
