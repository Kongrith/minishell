/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:22:37 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/20 11:17:52 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	int	i;

	if (DEBUG)
	{
		i = 0;
		while (++i < argc)
			printf("argv[%d]: %s\n", i, argv[i]);
	}
	else
		printf("test\n");
	return (0);
}
