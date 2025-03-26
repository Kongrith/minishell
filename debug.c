/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:01:23 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/25 10:16:47 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg_env(int argc, char **argv, char **envp)
{
	int	i;

	printf("argc: %d\n", argc);
	printf("----\n");
	i = 0;
	while (argv[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf("----\n");
	i = 0;
	while (envp[i] != NULL)
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
	printf("----\n");
}

void	print_env_list(t_env *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		printf("env_list[%ld]  name: %s  value: %s\n", \
			count, lst->name, lst->value);
		lst = lst->next;
		count++;
	}
	printf("----\n");
}
