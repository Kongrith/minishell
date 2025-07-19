/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:14:04 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/14 19:35:07 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_handler(t_sh *sh)
{
	if (!sh->input || !*sh->input)
		return ;
	add_history(sh->input);
	if (g_sigint_status)
	{
		sh->status = 130;
		g_sigint_status = 0;
	}
	if (DEBUG)
		printf("Debug -- line: %s\n", sh->input);
	lexer(sh);
	parser(sh);
	if (DEBUG)
		print_cmd_list(sh, sh->cmd_list);
	if (!check_single_redirection(sh, sh->cmd_list) && !sh->error)
	{
		if (fill_heredoc(sh, sh->cmd_list) == 0 && sh->status == 130)
			;
		else
			exec_commands(sh);
	}
	free_redi_list(sh);
	free_cmd_list(sh);
}
