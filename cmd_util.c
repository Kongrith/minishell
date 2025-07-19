/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:42:48 by rvesterl          #+#    #+#             */
/*   Updated: 2025/04/08 09:12:00 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_reg(char *cmd)
{
	struct stat	st;

	ft_memset(&st, 0, sizeof(st));
	stat(cmd, &st);
	return (S_ISREG(st.st_mode));
}

bool	is_dir(char *cmd)
{
	struct stat	st;

	ft_memset(&st, 0, sizeof(st));
	stat(cmd, &st);
	return (S_ISDIR(st.st_mode));
}

bool	is_exec(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (true);
	return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}
