/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:48:28 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/08 14:50:17 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	walk_space_sign(const char *s, int *sign)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\f' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\t' || s[i] == '\v')
		i++;
	if (s[i] == '-')
	{
		*sign *= -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	return (i);
}

long long	exit_atol(char *str)
{
	int			i;
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	i = walk_space_sign(str, &sign);
	while (str[i] != '\0')
	{
		if (sign > 0 && str[i] >= '0' && str[i] <= '9'
			&& result <= (LLONG_MAX - (str[i] - '0')) / 10)
			result = result * 10 + (str[i++] - '0');
		else if (sign < 0 && str[i] >= '0' && str[i] <= '9'
			&& result >= (LLONG_MIN + (str[i] - '0')) / 10)
			result = result * 10 - (str[i++] - '0');
		else
		{
			print_shell_error("exit", str);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(ERROR_NUMERIC_ARGUMENT, STDERR_FILENO);
			return (INT_MAX);
		}
	}
	return (result % 256);
}

void	exit_arg(t_sh *sh, t_cmd *cmd)
{
	sh->status = exit_atol(cmd->args[1]);
	if (sh->status == INT_MAX)
		exit(2);
	return ;
}

void	close_fds(t_sh *sh, t_cmd *cmd)
{
	restore_fd_std(&cmd->fd_in, &cmd->fd_out);
	close_redirections(sh->cmd_list);
}

void	b_exit(t_sh *sh, t_cmd *cmd)
{
	int	fd;

	if (sh->cmd_len == 1)
		close_fds(sh, cmd);
	fd = dup(STDOUT_FILENO);
	if (isatty(fd))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	close(fd);
	free_env_list(sh);
	free_sh(sh);
	rl_clear_history();
	if (!cmd->args[1])
	{
		free_cmd_list(sh);
		exit(sh->status);
	}
	exit_arg(sh, cmd);
	if (cmd->args[2])
	{
		free_cmd_list(sh);
		print_shell_error("exit", ERROR_TOO_MANY_ARGS);
		exit(1);
	}
	free_cmd_list(sh);
	exit(sh->status);
}
