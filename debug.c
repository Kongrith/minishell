/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:01:23 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/01 13:45:43 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg_env(int argc, char **argv, char **envp)
{
	int	i;

	printf("Debug -- argc: %d\n", argc);
	printf("----\n");
	i = 0;
	while (argv[i] != NULL)
	{
		printf("Debug -- argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf("----\n");
	i = 0;
	while (envp[i] != NULL)
	{
		printf("Debug -- envp[%d]: %s\n", i, envp[i]);
		i++;
	}
	printf("----\n");
}

void	print_env_list(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		printf("Debug -- env_list[%d]  name: %s  value: %s\n",
			count, lst->name, lst->value);
		lst = lst->next;
		count++;
	}
	printf("----\n");
}

void	print_rd_list(t_rd *lst)
{
	const char	*tp[] = {"RD_INPUT", "RD_OUTPUT", "RD_APPEND", "RD_HEREDOC"};
	int			rd_count;

	rd_count = 0;
	while (lst)
	{
		printf("    rd_list[%d]  type: %s  file_name: %s\n",
			rd_count, tp[lst->type], lst->file_name);
		printf("        content: %s  expand: %d\n",
			lst->content, lst->expand);
		printf("        fd: %d  rd_index: %d\n",
			lst->fd, lst->rd_index);
		lst = lst->next;
		rd_count++;
	}
}

void	print_cmd_list(t_sh *sh, t_cmd *lst)
{
	int	cmd_count;
	int	i;

	printf("Debug -- cmd_len: %d\n", sh->cmd_len);
	cmd_count = 0;
	while (lst)
	{
		printf("Debug -- cmd_list[%d]  cmd: %s\n", cmd_count, lst->cmd);
		printf("    fd_in: %d  fd_out: %d  builtin: %d  rd_counter: %d  ",
			lst->fd_in, lst->fd_out, lst->builtin, lst->rd_counter);
		printf("rd_in_last: %d, rd_out_last: %d\n",
			lst->rd_in_last, lst->rd_out_last);
		i = 0;
		while (lst->args[i] != NULL)
		{
			printf("    args[%d]: %s\n", i, lst->args[i]);
			i++;
		}
		print_rd_list(lst->rd_list);
		lst = lst->next;
		cmd_count++;
	}
	printf("----\n");
}
