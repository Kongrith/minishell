/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:54:35 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/01 13:34:12 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_list(t_sh *sh)
{
	int		i;
	char	*name;
	char	*value;
	char	*offset;

	sh->env_list = NULL;
	sh->env_len = 0;
	i = 0;
	while (sh->envp[i])
	{
		offset = ft_strchr(sh->envp[i], '=');
		if (offset)
		{
			name = env_name_dup(sh->envp[i], offset);
			value = env_value_dup(offset);
			add_env_entry(sh, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	sh->envp = NULL;
}

// Adds new environment variable, value will be updated if name exist.
void	add_env_entry(t_sh *sh, char *name, char *value)
{
	t_env	*new;

	if (update_env_entry(sh->env_list, name, value))
		return ;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		perror_exit("malloc", EXIT_FAILURE);
	new->name = ft_strdup(name);
	if (!new->name)
		perror_exit("malloc", EXIT_FAILURE);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			perror_exit("malloc", EXIT_FAILURE);
	}
	else
		new->value = NULL;
	if (DEBUG)
		printf("Debug -- Added env name '%s' with value '%s'\n", name, value);
	new->next = sh->env_list;
	sh->env_list = new;
	sh->env_len++;
}

t_env	*get_env_entry(t_env *env, char *name)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

bool	update_env_entry(t_env *env, char *name, char *updated_value)
{
	t_env	*lst;

	lst = get_env_entry(env, name);
	if (!lst)
		return (false);
	if (DEBUG)
		printf("Debug -- Updating env name '%s' from value '%s' to '%s'.\n",
			name, lst->value, updated_value);
	if (lst->value)
	{
		free(lst->value);
		lst->value = NULL;
	}
	lst->value = ft_strdup(updated_value);
	if (!lst->value)
		perror_exit("malloc", EXIT_FAILURE);
	return (true);
}

void	del_env_entry(t_sh *sh, char *name)
{
	t_env	*current;
	t_env	*previous;

	current = sh->env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (DEBUG)
				printf("Debug -- unset env variable: %s\n", name);
			if (previous)
				previous->next = current->next;
			else
				sh->env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			sh->env_len--;
			return ;
		}
		previous = current;
		current = current->next;
	}
}
