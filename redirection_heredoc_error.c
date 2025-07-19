/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc_error.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:17:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/10 14:18:58 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_malloc_error(t_sh *sh)
{
	print_shell_error(HEREDOC_ORIGIN, ERROR_MEMORY_ALLOCATION);
	sh->status = 1;
	exit(sh->status);
}

void	delimiter_error(char *delimiter)
{
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(ERROR_WHD, STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd(ERROR_HEREDOC_ENCLOSE, STDERR_FILENO);
}

void	eof_error(t_sh *sh, char *token)
{
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(ERROR_EOF, STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd(ERROR_EOF_ENCLOSE, STDERR_FILENO);
	sh->status = 2;
}
