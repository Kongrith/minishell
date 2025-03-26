/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:22:37 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/25 11:41:04 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_loop(t_sh *sh)
{
	while (1)
	{
		update_envp(sh);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		sh->input = readline(SHELL_PROMPT);
		if (!sh->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break;
		}
		if (ft_strncmp(sh->input, "exit", 4) == 0)
		{
			free(sh->input);
			break;
		}
		free(sh->input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_sh sh;

	// if (DEBUG)
	// 	print_arg_env(argc, argv, envp);
	init_shell(&sh, envp);
	minishell_loop(&sh);
	free_env_list(&sh);
	rl_clear_history();
	return (0);
}
