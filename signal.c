/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:30:13 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/26 09:52:50 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_interactive(int signum)
{
	if (DEBUG)
		printf("interactive sigint: %d\n", signum);
	g_sigint_status = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_noninteractive(int signum)
{
	if (DEBUG)
		printf("noninteractive sigint: %d\n", signum);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}
