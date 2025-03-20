/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:26:23 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/12 09:45:18 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_lstmap_pf(t_list *lst, t_pformat *pf, \
						void *(*f)(void *, t_pformat *), void (*del)(void *))
{
	t_list	*entry;
	t_list	*list;

	if (!lst || !f || !del)
		return (NULL);
	entry = ft_lstnew(f(lst->content, pf));
	if (!entry)
		return (NULL);
	list = entry;
	lst = lst->next;
	while (lst)
	{
		entry->next = ft_lstnew(f(lst->content, pf));
		if (!entry->next)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		lst = lst->next;
		entry = entry->next;
	}
	entry->next = NULL;
	return (list);
}
