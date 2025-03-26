/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:49:12 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/25 09:44:41 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_sh *sh, char **envp)
{
	ft_memset(sh, 0, sizeof(*sh));
	sh->envp = envp;
	sh->status = 0;
	init_env_list(sh);
	if (DEBUG)
		print_env_list(sh->env_list);
}
