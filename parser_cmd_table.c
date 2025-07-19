/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 06:46:48 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/15 12:22:33 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_args(t_sh *sh, t_cmd *new_node, char **args)
{
	int	i;
	int	first_flag;

	i = 0;
	first_flag = 1;
	init_parser(sh);
	while (i < count_pointer_to_array(args))
	{
		if (eval_redi(args[i]) && !sh->file_flag)
			assign_redi(sh, new_node, args[i], &first_flag);
		else if (sh->file_flag)
			assign_file(sh, new_node, args[i], &first_flag);
		else if (eval_cmd(args[i]) && sh->cmd_flag)
			assign_cmd(sh, new_node, args[i]);
		else
			assign_arg(sh, new_node, args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	new_node->args[sh->cmd_indx] = NULL;
	sh->redi_indx = 0;
}

static t_cmd	*create_node(t_sh *sh, char **args)
{
	t_cmd	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->builtin = 0;
	new_node->rd_counter = count_redirection(args);
	new_node->rd_in_last = -1;
	new_node->rd_out_last = -1;
	new_node->fd_in = STDIN_FILENO;
	new_node->fd_out = STDOUT_FILENO;
	new_node->args = ft_calloc(count_pointer_to_array(args) + 1, \
sizeof(char *));
	new_node->rd_list = NULL;
	new_node->next = NULL;
	fill_args(sh, new_node, args);
	return (new_node);
}

static t_cmd	*fill_table(t_sh *sh, int start, int end)
{
	t_cmd	*new_node;
	int		i;
	char	**args;

	args = (char **)ft_calloc(end - start + 1, sizeof(char *));
	i = 0;
	while (start + i < end)
	{
		args[i] = ft_strdup(sh->pre_cmd[start + i]);
		i++;
	}
	args[i] = NULL;
	new_node = create_node(sh, args);
	return (new_node);
}

static t_cmd	**command_table(t_sh *sh, t_cmd **tmp, int i, int cur)
{
	t_cmd	*new_node;

	if (i == 0)
	{
		new_node = fill_table(sh, i, cur);
		*tmp = new_node;
	}
	else
	{
		(*tmp)->next = fill_table(sh, i, cur);
		tmp = &(*tmp)->next;
	}
	sh->cmd_len += 1;
	return (tmp);
}

void	parse_input(t_sh *sh)
{
	t_cmd	**tmp;
	int		i;
	int		cur;

	tmp = &sh->cmd_list;
	i = 0;
	cur = 0;
	while (sh->pre_cmd[cur] != NULL)
	{
		if (ft_strcmp(sh->pre_cmd[cur], "|") == 0)
		{
			tmp = command_table(sh, tmp, i, cur);
			i = cur + 1;
		}
		cur++;
	}
	tmp = command_table(sh, tmp, i, cur);
	if (sh->pre_cmd)
	{
		free_double_ptr(sh->pre_cmd);
		sh->pre_cmd = NULL;
	}
	eval_last_redi(sh);
}
