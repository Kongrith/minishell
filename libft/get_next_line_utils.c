/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:59:45 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/10 09:55:36 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list) * 1);
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

t_fileinfo	*ft_fileinfonew(int fd)
{
	t_fileinfo	*fi;

	fi = malloc(sizeof(t_fileinfo) * 1);
	if (!fi)
		return (NULL);
	fi->fd = fd;
	fi->line_pos = 0;
	fi->buf_pos = 0;
	fi->bytes_left = 0;
	fi->buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!fi->buf)
	{
		free(fi);
		return (NULL);
	}
	return (fi);
}

void	ft_lstadd_front(t_list **lst, t_list *lst_new)
{
	if (!lst || !lst_new)
		return ;
	lst_new->next = *lst;
	*lst = lst_new;
}

t_fileinfo	*ft_get_fd(t_list *lst, int fd)
{
	t_fileinfo	*fi;

	if (!lst)
		return (NULL);
	while (lst)
	{
		fi = lst->content;
		if (fi->fd == fd)
			return (fi);
		lst = lst->next;
	}
	return (NULL);
}
