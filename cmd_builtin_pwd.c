/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:49:40 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/04 11:50:23 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(t_sh *sh)
{
	if (!sh->cwd)
	{
		sh->cwd = getcwd(NULL, 0);
		print_cwd_error(ERROR_ORIGIN_PWD);
		return (1);
	}
	ft_putendl_fd(sh->cwd, STDOUT_FILENO);
	return (0);
}
