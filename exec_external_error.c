/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:37:13 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/09 16:24:56 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_error(t_sh *sh, char *full_cmd_path)
{
	if (errno == ENOENT)
	{
		if (ft_strchr(full_cmd_path, '/'))
			print_shell_error(full_cmd_path, ERROR_FILE_NOT_FOUND);
		else
			print_shell_error(full_cmd_path, ERROR_CMD_NOT_FOUND);
		sh->status = 127;
		return (127);
	}
	if (is_dir(full_cmd_path))
		print_shell_error(full_cmd_path, ERROR_IS_DIRECTORY);
	else
	{
		print_shell_error(full_cmd_path, strerror(errno));
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	sh->status = 126;
	return (126);
}

int	execve_cmd_error(t_sh *sh, char **full_cmd_path)
{
	sh->status = exec_cmd_error(sh, *full_cmd_path);
	if (*full_cmd_path)
		free(*full_cmd_path);
	exit(sh->status);
}

void	print_signal_error(int status)
{
	int			i;
	const int	sig_num[] = {SIGHUP, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS,
		SIGFPE, SIGSEGV, SIGALRM, SIGTTIN, SIGTTOU, SIGXCPU, SIGXFSZ,
		SIGPWR, SIGSYS, 0};
	const char	*sig_str[] = {"Hangup\n", "Quit (core dumped)\n",
		"Illegal instruction (core dumped)\n",
		"Trace/breakpoint trap (core dumped)\n",
		"Aborted (core dumped)\n", "Bus error (core dumped)\n",
		"Floating point exception (core dumped)\n",
		"Segmentation fault (core dumped)\n",
		"Alarm clock\n", "Stopped (tty input)\n",
		"Stopped (tty output)\n", "CPU time limit exceeded\n",
		"File size limit exceeded\n", "Power failure\n",
		"Bad system call (core dumped)\n"};

	i = -1;
	while (sig_num[++i])
	{
		if (status == sig_num[i])
		{
			ft_putstr_fd((char *)sig_str[i], STDERR_FILENO);
			break ;
		}
	}
}
