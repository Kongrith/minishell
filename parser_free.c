/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:47:25 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/15 14:20:06 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
		}
		i++;
	}
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

static void	free_cmd(t_sh *sh)
{
	if (sh->pre_cmd)
	{
		free_double_ptr(sh->pre_cmd);
		sh->pre_cmd = NULL;
	}
}

void	free_cmd_list(t_sh *sh)
{
	t_cmd	*tmp;

	if (sh->cmd_list)
	{
		while (sh->cmd_list)
		{
			tmp = sh->cmd_list;
			sh->cmd_list = sh->cmd_list->next;
			if (tmp->cmd)
				free(tmp->cmd);
			if (tmp->args)
				free_double_ptr(tmp->args);
			if (tmp)
				free(tmp);
		}
		if (sh->cmd_list)
		{
			free(sh->cmd_list);
			sh->cmd_list = NULL;
		}
	}
	else
		free_cmd(sh);
}

static void	free_redi_data(t_cmd *tmp)
{
	t_rd	*redi;

	redi = tmp->rd_list;
	tmp->rd_list = tmp->rd_list->next;
	if (redi->file_name)
	{
		free(redi->file_name);
		redi->file_name = NULL;
	}
	if (redi->content)
	{
		free(redi->content);
		redi->content = NULL;
	}
	if (redi)
	{
		free(redi);
		redi = NULL;
	}
}

void	free_redi_list(t_sh *sh)
{
	t_cmd	*tmp;

	if (sh->cmd_list)
	{
		tmp = sh->cmd_list;
		while (tmp)
		{
			if (tmp->rd_list)
			{
				while (tmp->rd_list)
					free_redi_data(tmp);
				if (tmp->rd_list)
				{
					free(tmp->rd_list);
					tmp->rd_list = NULL;
				}
			}
			tmp = tmp->next;
		}
	}
}
