/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:06:13 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/16 08:14:43 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_err_msg(int err_code, char *err_token)
{
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	if (err_code == 3)
	{
		ft_putstr_fd("The real bash will request for the missing command. \
For minishell it out of scope.\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	if (err_code == 1)
		ft_putstr_fd(ERROR_TOKEN_NEWLINE, STDERR_FILENO);
	else if (err_code == 2)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(err_token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
}

static void	pre_parser_checking(t_sh *sh, int len)
{
	int		i;
	char	*err_msg;

	i = 0;
	while (sh->pre_cmd[i])
	{
		chk_missing_filename(sh, i);
		if (sh->error)
		{
			err_msg = sh->pre_cmd[i + 1];
			break ;
		}
		chk_empty_pipeline(sh, i, len);
		if (sh->error)
		{
			err_msg = sh->pre_cmd[i];
			break ;
		}
		i++;
	}
	if (sh->error)
	{
		show_err_msg(sh->error, err_msg);
		sh->status = 2;
	}
}

void	parser(t_sh *sh)
{
	int	len;

	if (!sh->error)
	{
		sh->error = 0;
		len = count_pointer_to_array(sh->pre_cmd);
		pre_parser_checking(sh, len);
	}
	if (!sh->error)
	{
		sh->cmd_len = 0;
		parse_input(sh);
	}
}
