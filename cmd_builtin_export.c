/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:56:29 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 11:31:37 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_name_error(t_sh *sh, char *name, char *value)
{
	char	*tmp1;
	char	*tmp2;
	char	*error_str;

	if (value[0])
	{
		tmp1 = ft_strjoin(name, "=");
		tmp2 = ft_strjoin(tmp1, value);
		free(tmp1);
		error_str = ft_strjoin(tmp2, "': ");
		free(tmp2);
	}
	else
		error_str = ft_strjoin(name, "': ");
	ft_putstr_fd(SHELL_ERROR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(ERROR_ORIGIN_EXPORT, STDERR_FILENO);
	ft_putstr_fd(error_str, STDERR_FILENO);
	ft_putstr_fd(ERROR_INVALID_IDENTIFIER, STDERR_FILENO);
	free(error_str);
	sh->status = 1;
}

bool	validate_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (false);
	if (!((name[0] >= 'a' && name[0] <= 'z')
			|| (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_'))
		return (false);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

t_env	*arg_to_env(t_sh *sh, char *arg)
{
	t_env	*result;
	char	*offset;

	result = ft_calloc(1, sizeof(t_env));
	offset = ft_strchr(arg, '=');
	if (offset)
	{
		result->name = env_name_dup(arg, offset);
		result->value = env_value_dup(offset);
		if (validate_name(result->name))
		{
			if (DEBUG)
				printf("Debug -- Env name valid: %s\n", result->name);
			return (result);
		}
		print_export_name_error(sh, result->name, result->value);
		free(result->name);
		free(result->value);
	}
	else if (ft_strlen(arg) && !validate_name(arg))
		print_export_name_error(sh, arg, "");
	free(result);
	return (NULL);
}

void	free_export_lst(t_env *lst)
{
	if (lst->name)
		free(lst->name);
	if (lst->value)
		free(lst->value);
	if (lst)
		free(lst);
}

int	b_export(t_sh *sh, t_cmd *cmd)
{
	int		i;
	t_env	*lst;

	sh->status = 0;
	if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (cmd->args[i])
			{
				lst = arg_to_env(sh, cmd->args[i]);
				if (!lst)
					continue ;
				add_env_entry(sh, lst->name, lst->value);
				free_export_lst(lst);
			}
		}
	}
	else
		export_no_arg(sh);
	return (sh->status);
}
