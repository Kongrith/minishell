/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 08:45:44 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/13 13:34:45 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Remove the mock stuff when parser is complete.

#include "minishell.h"

void	free_seg(char **seg)
{
	int	i;

	i = 0;
	while (seg[i])
	{
		free(seg[i]);
		i++;
	}
	free(seg);
}

// Counts the number of segments and trims single and double quotes.
int	count_trim_seg(char **seg)
{
	int		i;
	char	*s;

	i = 0;
	while (seg && seg[i])
	{
		s = ft_strtrim(seg[i], "'\"");
		if (s)
		{
			free(seg[i]);
			seg[i] = s;
		}
		if (DEBUG)
			printf("Debug -- trimmed args[%d]: %s\n", i, seg[i]);
		i++;
	}
	return (i);
}

// This function mocks a command list entry but splitting the command line
// string into args and assuming naively the first part entered is the command,
// the rest are the command arguments. It is needed in execution before we have 
// a working parser.
t_cmd	*mock_cmd(char *input)
{
	t_cmd	*cmd_list;
	char	**seg;
	int		i;
	int		seg_count;

	seg = ft_split(input, ' ');
	if (!seg)
		return (NULL);
	seg_count = count_trim_seg(seg);
	if (seg_count == 0)
	{
		free_seg(seg);
		return (NULL);
	}
	cmd_list = ft_calloc(1, sizeof(t_cmd));
	cmd_list->cmd = ft_strdup(seg[0]);
	cmd_list->args = ft_calloc(seg_count + 1, sizeof(char *));
	i = -1;
	while (++i < seg_count)
		cmd_list->args[i] = ft_strdup(seg[i]);
	cmd_list->args[i] = NULL;
	free_seg(seg);
	return (cmd_list);
}
