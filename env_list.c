/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:54:35 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:51 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_list(t_sh *sh)
{
	size_t	i;
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
			add_env_list(sh, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	sh->envp = NULL;
}

void	update_envp(t_sh *sh)
{
	t_env	*tmp;
	size_t	i;

	if (sh->envp != NULL)
		free_envp(sh->envp);
	sh->envp = malloc(sizeof(*sh->envp) * (sh->env_len + 1));
	if (!sh->envp)
		perror_exit("malloc", EXIT_FAILURE);
	tmp = sh->env_list;
	i = 0;
	while (tmp)
	{
		sh->envp[i] = env_list_to_envp(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	sh->envp[i] = NULL;
}

void	add_env_list(t_sh *sh, char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
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
	new->next = sh->env_list;
	sh->env_list = new;
	sh->env_len++;
}

t_env	*get_env(t_env *env, char *name)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strncmp(lst->name, name, ft_strlen(name)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
