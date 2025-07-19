/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:37:37 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/16 14:06:58 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *str, int *pos)
{
	char	*token;

	token = substring_and_remove_quotes(str, pos, '\'');
	return (token);
}

char	*handle_double_quote(t_sh *sh, char *str, int *pos)
{
	char	*token;
	char	*expand_token;
	int		start;
	int		cur;

	token = substring_and_remove_quotes(str, pos, '\"');
	if (ft_strchr(token, '$') == NULL)
		return (token);
	start = ft_strchr(token, '$') - token;
	cur = start;
	while (cur < (int)ft_strlen(token))
	{
		expand_token = handle_dollar_sign(sh, token, &cur, 1);
		if (expand_token == NULL)
			expand_token = ft_strdup("");
		token = insert_expand_string(token, expand_token, start, cur);
		if (cur >= (int)ft_strlen(token))
			return (token);
		start = ft_strchr(token + cur, '$') - token;
		cur = start;
		if (start < 0)
			break ;
	}
	return (token);
}

static char	*dollar_sign_management(t_sh *sh, char *arg, int *flag, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (*flag == 0 && (arg[*i + 1] == '\'' || arg[*i + 1] == '\"'))
	{
		(*i)++;
		if (arg[*i] == '\'')
			tmp = handle_single_quote(arg, i);
		else if (arg[*i] == '\"')
			tmp = handle_double_quote(sh, arg, i);
	}
	else
		tmp = handle_dollar_sign(sh, arg, i, 0);
	return (tmp);
}

static char	*dequote_handler(t_sh *sh, char *arg, int *flag, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (arg[*i] == '\'')
	{
		tmp = handle_single_quote(arg, i);
		(*flag) += 1;
	}
	else if (arg[*i] == '\"')
	{
		tmp = handle_double_quote(sh, arg, i);
		(*flag) += 1;
	}
	else if (arg[*i] == '$')
		tmp = dollar_sign_management(sh, arg, flag, i);
	else
		tmp = handle_charactor(arg, i);
	return (tmp);
}

char	*dequote(t_sh *sh, char *arg)
{
	char	*dequote_arg;
	char	*tmp;
	int		i;
	int		flag;

	dequote_arg = (char *)ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	dequote_arg[0] = '\0';
	i = 0;
	flag = 0;
	while (arg[i])
	{
		tmp = dequote_handler(sh, arg, &flag, &i);
		if (tmp == NULL)
		{
			safe_free(dequote_arg);
			return (NULL);
		}
		dynamic_token_size(&dequote_arg, arg, tmp);
		ft_strcat(dequote_arg, tmp);
		safe_free(tmp);
		i++;
	}
	if (ft_strchr(dequote_arg, '~') != NULL && flag == 0)
		dequote_arg = expand_path(sh, dequote_arg);
	return (dequote_arg);
}
