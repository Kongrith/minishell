/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:52:18 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/09 15:48:57 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

// Finds command path by searching given environment list and verifies that
// the command can be executed.
// Returns full path to the command if found, otherwise NULL.
char	*find_cmd_path(t_sh *sh, char *cmd)
{
	t_env	*entry;
	char	*tmp;
	char	**paths;
	char	*cmd_path;
	int		i;

	entry = get_env_entry(sh->env_list, "PATH");
	if (!entry)
		return (NULL);
	paths = ft_split(entry->value, ':');
	i = -1;
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0 && ft_strlen(cmd))
			return (free_paths(paths), cmd_path);
		free(cmd_path);
	}
	free_paths(paths);
	return (NULL);
}

char	*check_cmd_path(t_sh *sh, char *cmd)
{
	if (access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_cmd_path(sh, cmd));
}
