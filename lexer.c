/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:05:53 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/14 19:36:43 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*whitespace_split(char *input, int *i)
{
	char	*token;

	token = NULL;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\0')
		return (token);
	if (is_operator(input[*i]))
		token = handle_operator(input, i);
	else
		token = handle_charactor_and_quotes(input, i);
	return (token);
}

static void	tokenizer(t_sh *sh)
{
	int		i;
	int		j;
	char	**tokens;
	char	*token;
	int		token_size;

	token_size = TOKEN_SIZE;
	tokens = (char **)ft_calloc(token_size, sizeof(char *));
	i = 0;
	j = 0;
	while (sh->input[i] != '\0')
	{
		token = whitespace_split(sh->input, &i);
		if (token != NULL)
		{
			dynamic_segment_size(&tokens, &token_size, j);
			tokens[j++] = ft_strdup(token);
			if (token)
				free(token);
		}
	}
	tokens[j] = NULL;
	sh->pre_cmd = tokens;
}

static void	lexical_analysis(t_sh *sh)
{
	int	i;

	i = 0;
	sh->error = 0;
	while (sh->input[i])
	{
		if (sh->input[i] == '\'')
			chk_unclosed_quotes(sh, &i, '\'');
		else if (sh->input[i] == '\"')
			chk_unclosed_quotes(sh, &i, '\"');
		if (sh->error)
			break ;
		i++;
	}
	if (sh->error)
	{
		ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
		ft_putstr_fd(ERROR_UNCLOSED_QUOTES, STDERR_FILENO);
		sh->status = 2;
	}
}

void	lexer(t_sh *sh)
{
	lexical_analysis(sh);
	if (sh->error)
		return ;
	tokenizer(sh);
}
