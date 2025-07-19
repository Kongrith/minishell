/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 05:54:58 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/15 14:22:09 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dequote_without_expansion(char *arg)
{
	char	*dequote_arg;
	char	*tmp;
	int		i;
	int		flag;

	tmp = NULL;
	dequote_arg = (char *)ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	dequote_arg[0] = '\0';
	i = 0;
	flag = 0;
	while (arg[i])
	{
		tmp = filename_handler(arg, &flag, &i);
		dynamic_token_size(&dequote_arg, arg, tmp);
		ft_strcat(dequote_arg, tmp);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
	return (dequote_arg);
}

static void	dequote_filename(t_rd *redi, char *arg, int *first_flag)
{
	char	*dequote_arg;

	dequote_arg = dequote_without_expansion(arg);
	redi->file_name = ft_strdup(dequote_arg);
	if (dequote_arg)
		free(dequote_arg);
	if (*first_flag)
		*first_flag = 0;
}

void	assign_file(t_sh *sh, t_cmd *new_node, char *arg, int *first_flag)
{
	t_rd	*redi;

	sh->file_flag = 0;
	if (*first_flag)
	{
		if (new_node->rd_list->type == RD_HEREDOC && \
(ft_strchr(arg, '\'') == NULL && ft_strchr(arg, '\"') == NULL))
			new_node->rd_list->expand = true;
		dequote_filename(new_node->rd_list, arg, first_flag);
	}
	else
	{
		redi = new_node->rd_list;
		while (redi->next != NULL)
			redi = redi->next;
		if (redi->type == RD_HEREDOC && \
(ft_strchr(arg, '\'') == NULL && ft_strchr(arg, '\"') == NULL))
			redi->expand = true;
		dequote_filename(redi, arg, first_flag);
	}
}

void	eval_last_redi(t_sh *sh)
{
	t_cmd	*tmp;
	t_rd	*redi;

	tmp = sh->cmd_list;
	while (tmp)
	{
		if (tmp->rd_list)
		{
			redi = tmp->rd_list;
			while (redi)
			{
				if (redi->type == RD_INPUT || redi->type == RD_HEREDOC)
					tmp->rd_in_last = redi->rd_index;
				else
					tmp->rd_out_last = redi->rd_index;
				redi = redi->next;
			}
		}
		tmp = tmp->next;
	}
}

void	assign_redi(t_sh *sh, t_cmd *new_node, char *str, int *first_flag)
{
	t_rd	*new_redi;
	t_rd	*redi;

	sh->file_flag = 1;
	new_redi = ft_calloc(1, sizeof(t_rd));
	new_redi->type = eval_token_type(str);
	new_redi->expand = false;
	new_redi->next = NULL;
	redi = new_node->rd_list;
	if (*first_flag)
	{
		new_redi->rd_index = 0;
		new_node->rd_list = new_redi;
		sh->redi_indx += 1;
		*first_flag = 0;
	}
	else
	{
		new_redi->rd_index = sh->redi_indx;
		sh->redi_indx += 1;
		while (redi->next != NULL)
			redi = redi->next;
		redi->next = new_redi;
	}
}
