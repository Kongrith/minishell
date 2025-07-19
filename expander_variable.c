/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:17:38 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/15 23:14:09 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_sh *sh, char *env)
{
	t_env	*str;

	str = get_env_entry(sh->env_list, env);
	if (env)
		free(env);
	if (!str)
		return (NULL);
	else if (ft_strcmp(str->value, "") == 0)
		return (NULL);
	else
		return (ft_strdup(str->value));
}

static char	*extract_env_variable(char *str, int start, int len)
{
	char	*tmp;

	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	ft_strncpy(tmp, str + start + 1, len);
	tmp[len] = '\0';
	return (tmp);
}

static char	*ret_status_expander(int ret_status)
{
	char	*buf;
	char	*tmp;

	buf = ft_itoa(ret_status);
	tmp = ft_strdup(buf);
	free(buf);
	return (tmp);
}

static char	*expander_handler(t_sh *sh, char *str, int start, int *cur)
{
	char	*tmp;
	int		len;

	len = (*cur) - start;
	if (len == 1 && str[(*cur)] != '?')
		tmp = ft_strdup("$");
	else if (str[(*cur)] == '?')
	{
		(*cur)++;
		tmp = ret_status_expander(sh->status);
	}
	else
		tmp = expand_variable(sh, extract_env_variable(str, start, len - 1));
	return (tmp);
}

char	*handle_dollar_sign(t_sh *sh, char *str, int *pos, int flag)
{
	char	*tmp;
	int		start;
	int		cur;

	start = *pos;
	cur = *pos;
	while (str[cur] != '\0' && (str[cur] != '?' && str[cur] != '/' && \
!ft_isquotes(str[cur]) && !ft_isspace(str[cur]) && !is_operator(str[cur])))
	{
		cur++;
		if (str[cur] == '$')
			break ;
	}
	tmp = expander_handler(sh, str, start, &cur);
	if (flag)
		*pos = cur;
	else
		*pos = cur - 1;
	return (tmp);
}
