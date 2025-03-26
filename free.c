/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:18:46 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/24 17:06:30 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i])
			free(envp[i]);
		i++;
	}
	if (envp)
		free(envp);
}

void	free_env_list(t_sh *sh)
{
	t_env	*tmp;

	if (sh->env_list)
	{
		while (sh->env_list)
		{
			tmp = sh->env_list;
			sh->env_list = sh->env_list->next;
			if (tmp->name)
				free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			if (tmp)
				free(tmp);
		}
		free(sh->env_list);
	}
	if (sh->envp)
		free_envp(sh->envp);
}
