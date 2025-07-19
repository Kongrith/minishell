/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:47:23 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 13:20:20 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_error(char *arg, char *error)
{
	ft_putstr_fd("env: ‘", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("’: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
}

int	b_env(t_sh *sh, t_cmd *cmd)
{
	t_env	*lst;
	char	*test;

	test = NULL;
	if (cmd->args[1])
	{
		test = check_cmd_path(sh, cmd->args[1]);
		if (test)
		{
			print_shell_error(cmd->args[0], ERROR_NOT_IMPLEMENTED);
			free(test);
			return (1);
		}
		print_env_error(cmd->args[1], ERROR_FILE_NOT_FOUND);
		return (127);
	}
	lst = sh->env_list;
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (0);
}
