/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 04:20:28 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/16 08:16:50 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	chk_operator(char *str)
{
	int	error;

	error = 0;
	if (check_cmd(str, "<") || check_cmd(str, "<<") || check_cmd(str, ">") || \
check_cmd(str, ">>") || check_cmd(str, "|") || check_cmd(str, "||") || \
check_cmd(str, "&") || check_cmd(str, "&&"))
		error = 2;
	return (error);
}

void	chk_missing_filename(t_sh *sh, int i)
{
	if (eval_redi(sh->pre_cmd[i]))
	{
		if ((sh->pre_cmd[i + 1]) == NULL)
			sh->error = 1;
		else if (chk_operator(sh->pre_cmd[i + 1]))
			sh->error = 2;
	}
}

void	chk_unclosed_quotes(t_sh *sh, int *i, char c)
{
	if (ft_strchr(sh->input + *i + 1, c) == NULL)
		sh->error = 1;
	else
		*i = next_index_from_str(sh->input, *i, c);
}

void	chk_empty_pipeline(t_sh *sh, int i, int len)
{
	char	**token;

	token = sh->pre_cmd;
	if (i == 0)
	{
		if (check_cmd(token[i], "|") || check_cmd(token[i], "||") || \
check_cmd(token[i], "&") || check_cmd(token[i], "&&"))
			sh->error = 2;
	}
	else if ((i != 0) && (i != len - 1))
	{
		if (check_cmd(token[i], "|") || check_cmd(token[i], "||") || \
check_cmd(token[i], "&") || check_cmd(token[i], "&&"))
		{
			if (check_cmd(token[i + 1], "|") || check_cmd(token[i + 1], "||") || \
check_cmd(token[i + 1], "&") || check_cmd(token[i + 1], "&&"))
				sh->error = 2;
		}
	}
	else if (i == len - 1)
	{
		if (check_cmd(token[i], "|") || check_cmd(token[i], "||") || \
check_cmd(token[i], "&") || check_cmd(token[i], "&&"))
			sh->error = 3;
	}
}
