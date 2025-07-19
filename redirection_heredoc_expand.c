/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc_expand.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:31:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/16 16:33:28 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit(t_sh *sh)
{
	char	*status;

	status = ft_itoa(sh->status);
	if (!status)
	{
		heredoc_malloc_error(sh);
		return (NULL);
	}
	return (status);
}

char	*expand_var_two(t_sh *sh, const char **pointer)
{
	char	*name;
	char	*value;

	name = env_name(pointer);
	if (!name)
	{
		print_syntax_error(sh, ERROR_TOKEN_DOLLAR);
		return (ft_strdup("$"));
	}
	if (ft_strcmp(name, "?") == 0)
	{
		value = ft_itoa(sh->status);
		free(name);
		return (value);
	}
	value = env_value(sh, name);
	if (!value)
		return (ft_strdup(""));
	free(name);
	return (ft_strdup(value));
}

char	*expand_single(t_sh *sh, const char **string)
{
	char	*result;

	if (!string || !*string || !**string)
	{
		eof_error(sh, "");
		return (NULL);
	}
	if (**string == '$')
	{
		if (*(*string + 1) == '?')
		{
			(*string += 2);
			return (expand_exit(sh));
		}
		else
			return (expand_var_two(sh, string));
	}
	result = ft_strndup(*string, 1);
	if (!result)
		return (NULL);
	result[0] = **string;
	result[1] = '\0';
	(*string)++;
	return (result);
}

char	*expand_append(t_sh *sh, char *result, char *expanded)
{
	char	*new;

	new = ft_strjoin(result, expanded);
	free(expanded);
	free(result);
	if (!new)
		heredoc_malloc_error(sh);
	return (new);
}

char	*quote_expand(t_sh *sh, char *string)
{
	char	*result;
	char	*expanded;

	if (!string)
		return (eof_error(sh, ""), NULL);
	result = ft_strdup("");
	if (!result)
		heredoc_malloc_error(sh);
	while (*string)
	{
		expanded = expand_single(sh, (const char **)&string);
		if (!expanded)
		{
			free(result);
			return (NULL);
		}
		result = expand_append(sh, result, expanded);
		if (!result)
			return (NULL);
	}
	return (result);
}
