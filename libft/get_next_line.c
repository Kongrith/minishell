/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:44:45 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/30 13:59:19 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_lf_check(char *line, size_t bytes_read, t_fileinfo *fi)
{
	size_t	i;

	i = fi->buf_pos;
	while (i < bytes_read)
	{
		if (fi->buf[i++] == '\n')
		{
			line = ft_append_line(line, i - fi->buf_pos, 1, fi);
			if (i == bytes_read)
				fi->buf_pos = 0;
			else
				fi->buf_pos = i;
			fi->bytes_left = bytes_read;
			fi->line_pos = 0;
			return (line);
		}
	}
	if (bytes_read == BUFFER_SIZE)
	{
		line = ft_append_line(line, bytes_read - fi->buf_pos, 0, fi);
		fi->buf_pos = 0;
	}
	fi->bytes_left = 0;
	return (line);
}

char	*ft_append_line(char *line, ssize_t len, int t, t_fileinfo *fi)
{
	char	*result;

	if (len == 0 && t == 0)
		return (line);
	if (len == 0 && t == 1 && fi->line_pos == 0)
		return (NULL);
	result = malloc(sizeof(char) * (fi->line_pos + len + t));
	if (!result)
		return (NULL);
	if (line)
	{
		ft_memcpy(result, line, fi->line_pos);
		free(line);
	}
	ft_memcpy(&result[fi->line_pos], &fi->buf[fi->buf_pos], len);
	fi->line_pos += len;
	if (t == 1)
		result[fi->line_pos] = '\0';
	return (result);
}

char	*ft_clean_up(char *line, t_fileinfo *fi, t_list **lst)
{
	t_list	*a;
	t_list	*b;

	a = *lst;
	while (a)
	{
		b = a->next;
		if (a->content == fi)
		{
			*lst = b;
			free(a);
			break ;
		}
		else if (b->content == fi)
		{
			a->next = b->next;
			free(b);
			break ;
		}
		a = b;
	}
	free(fi->buf);
	free(fi);
	return (line);
}

char	*ft_read_line(int fd, t_fileinfo *fi, t_list **lst)
{
	ssize_t	bytes_read;
	char	*line;

	line = NULL;
	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE)
	{
		if (!fi->buf_pos)
		{
			bytes_read = read(fd, fi->buf, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				(free(line), line = NULL);
				return (ft_clean_up(line, fi, lst));
			}
		}
		else
			bytes_read = fi->bytes_left;
		line = ft_lf_check(line, bytes_read, fi);
		if (fi->bytes_left > 0)
			return (line);
	}
	line = ft_append_line(line, bytes_read - fi->buf_pos, 1, fi);
	return (ft_clean_up(line, fi, lst));
}

char	*get_next_line(int fd)
{
	static t_list	*lst_fd;
	t_list			*lst_new;
	t_fileinfo		*fi;

	fi = ft_get_fd(lst_fd, fd);
	if (!fi)
	{
		fi = ft_fileinfonew(fd);
		if (!fi)
			return (NULL);
		if (!lst_fd)
		{
			lst_fd = ft_lstnew(fi);
			if (!lst_fd)
				return (NULL);
		}
		else
		{
			lst_new = ft_lstnew(fi);
			if (!lst_new)
				return (NULL);
			ft_lstadd_front(&lst_fd, lst_new);
		}
	}
	return (ft_read_line(fd, fi, &lst_fd));
}
