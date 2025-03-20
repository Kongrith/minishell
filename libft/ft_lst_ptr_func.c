/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_ptr_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:29:54 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/13 10:29:00 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_lst_seg_content(void *lst_content)
{
	if (!lst_content)
		return ;
	free(lst_content);
}

void	del_lst_res_content(void *lst_content)
{
	t_cont	*cs;

	if (!lst_content)
		return ;
	cs = lst_content;
	free(cs->seg);
	free(cs);
}

void	print_lst_seg(void *lst_content)
{
	t_cont	*cs;

	if (!lst_content)
		return ;
	cs = lst_content;
	write(STDOUT_FILENO, cs->seg, cs->len);
}
