/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_export_no_arg.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:30:58 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/06 12:34:57 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **d, int i, int j)
{
	char	*temp;

	temp = d[i];
	d[i] = d[j];
	d[j] = temp;
}

void	sort_env(char **d, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(d[j], d[j + 1]) > 0)
				swap(d, j, j + 1);
			j++;
		}
		i++;
	}
}

void	export_no_arg(t_sh *sh)
{
	int	i;

	sort_env(sh->envp, sh->env_len);
	i = 0;
	while (sh->envp[i] != NULL)
	{
		printf("declare -x %s\n", sh->envp[i]);
		i++;
	}
}
