/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:25:15 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 11:31:46 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(char *error, int rc)
{
	perror(error);
	exit(rc);
}

void	print_shell_error(char *cmd, char *error)
{
	char	*cmd_str;

	cmd_str = ft_strjoin(cmd, ": ");
	if (!cmd_str)
		perror_exit("malloc", EXIT_FAILURE);
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(cmd_str, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	free(cmd_str);
}

void	print_shell_p_error(char *cmd, char *p_error)
{
	char	*cmd_str;

	cmd_str = ft_strjoin(cmd, ": ");
	if (!cmd_str)
		perror_exit("malloc", EXIT_FAILURE);
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(cmd_str, STDERR_FILENO);
	perror(p_error);
	free(cmd_str);
}

void	print_cwd_error(char *origin)
{
	char	*origin_str;

	origin_str = ft_strjoin(origin, ": ");
	if (!origin_str)
		perror_exit("malloc", EXIT_FAILURE);
	ft_putstr_fd(origin_str, STDERR_FILENO);
	ft_putstr_fd(ERROR_RETRIEVING_DIR, STDERR_FILENO);
	perror(ERROR_ORIGIN_GETCWD ERROR_CANNOT_ACCESS_PARENT);
	free(origin_str);
}

int	print_syntax_error(t_sh *sh, char *token)
{
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	sh->status = 2;
	return (1);
}
