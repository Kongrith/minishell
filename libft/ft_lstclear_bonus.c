/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:36:08 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/02 09:49:48 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*foo;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		foo = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = foo;
	}
}
