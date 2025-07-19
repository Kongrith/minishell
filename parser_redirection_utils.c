/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 04:14:13 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/15 14:20:54 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirection(char **args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (args[i] != NULL && ft_strcmp(args[i], "|") != 0)
	{
		if (eval_redi(args[i]))
			len++;
		i++;
	}
	return (len);
}

bool	eval_redi(char *cmd)
{
	if (check_cmd(cmd, "<") || check_cmd(cmd, ">") || \
check_cmd(cmd, "<<") || check_cmd(cmd, ">>"))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

t_rd_type	eval_token_type(char *token)
{
	if (token[0] == '<' && token[1] == '<')
		return (RD_HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (RD_APPEND);
	else if (token[0] == '>')
		return (RD_OUTPUT);
	else
		return (RD_INPUT);
}

char	*filename_handler(char *arg, int *flag, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (arg[*i] == '\'')
	{
		tmp = substring_and_remove_quotes(arg, i, '\'');
		(*flag) += 1;
	}
	else if (arg[*i] == '\"')
	{
		tmp = substring_and_remove_quotes(arg, i, '\"');
		(*flag) += 1;
	}
	else
		tmp = handle_charactor(arg, i);
	return (tmp);
}
