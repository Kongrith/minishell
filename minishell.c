/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:22:37 by rvesterl          #+#    #+#             */
/*   Updated: 2025/06/29 06:16:44 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_status;

void	minishell_loop(t_sh *sh)
{
	while (1)
	{
		g_sigint_status = 0;
		update_envp(sh);
		signal(SIGINT, signal_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		sh->input = readline(SHELL_PROMPT);
		if (!sh->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		input_handler(sh);
		free(sh->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	if (DEBUG)
		print_arg_env(argc, argv, envp);
	init_shell(&sh, envp);
	minishell_loop(&sh);
	free_env_list(&sh);
	free_sh(&sh);
	rl_clear_history();
	return (0);
}
