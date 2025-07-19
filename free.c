/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:18:46 by rvesterl          #+#    #+#             */
/*   Updated: 2025/06/29 05:16:36 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

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

void	free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		if (args[i])
			free(args[i]);
	free(args);
}

void	free_sh(t_sh *sh)
{
	if (sh->input)
		free(sh->input);
	if (sh->cwd)
		free(sh->cwd);
	if (sh->oldwd)
		free(sh->oldwd);
}
