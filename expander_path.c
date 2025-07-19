/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 04:32:54 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/14 22:02:12 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_string(const char *home, char *old_str)
{
	char	*new_str;

	new_str = (char *)ft_calloc(ft_strlen(home) + 1, sizeof(char));
	ft_strcpy(new_str, home);
	if (old_str)
	{
		free(old_str);
		old_str = NULL;
	}
	return (new_str);
}

char	*expand_path(t_sh *sh, char *org_str)
{
	char	*home;
	char	*new_str;
	int		len;

	home = get_env_entry(sh->env_list, "HOME")->value;
	len = ft_strlen(org_str);
	if (len == 1 && org_str[0] == '~')
		return (replace_string(home, org_str));
	else if (len > 1 && org_str[0] == '~' && org_str[1] == '/')
	{
		new_str = ft_calloc(ft_strlen(home) + \
ft_strlen(org_str) + 1, sizeof(char));
		new_str[0] = '\0';
		ft_strcpy(new_str, home);
		ft_strcat(new_str, org_str + 1);
		if (org_str != NULL)
			free(org_str);
		return (new_str);
	}
	else
		return (org_str);
}
