/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:47:19 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/02 11:30:55 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*entry;
	t_list	*list;

	if (!lst || !f || !del)
		return (NULL);
	entry = ft_lstnew(f(lst->content));
	if (!entry)
		return (NULL);
	list = entry;
	lst = lst->next;
	while (lst)
	{
		entry->next = ft_lstnew(f(lst->content));
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
