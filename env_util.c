/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:46:45 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/25 09:29:24 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_name_dup(char *envp_line, char *offset)
{
	char	*name;

	name = ft_calloc(offset - envp_line + 1, sizeof(char));
	if (!name)
		perror_exit("malloc", EXIT_FAILURE);
	ft_memcpy(name, envp_line, offset - envp_line);
	return (name);
}

char	*env_value_dup(char *offset)
{
	char	*value;

	value = ft_strdup(offset + 1);
	if (!value)
		perror_exit("malloc", EXIT_FAILURE);
	return (value);
}

char	*env_list_to_envp(char *name, char *value)
{
	char	*line;
	int		len_name;
	int		len_value;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	line = ft_calloc(len_name + len_value + 2, sizeof(char));
	if (!line)
		perror_exit("malloc", EXIT_FAILURE);
	ft_memcpy(line, name, len_name);
	line[len_name] = '=';
	ft_memcpy(&line[len_name] + 1, value, len_value);
	return (line);
}

void	update_envp(t_sh *sh)
{
	t_env	*tmp;
	int		i;

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
