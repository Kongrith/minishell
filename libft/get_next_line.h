/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:45 by rvesterl          #+#    #+#             */
/*   Updated: 2024/10/08 11:33:40 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fileinfo
{
	int		fd;
	size_t	line_pos;
	size_t	buf_pos;
	ssize_t	bytes_left;
	char	*buf;
}	t_fileinfo;

char		*get_next_line(int fd);
t_list		*ft_lstnew(void *content);
t_fileinfo	*ft_fileinfonew(int fd);
void		ft_lstadd_front(t_list **lst, t_list *lst_new);
t_fileinfo	*ft_get_fd(t_list *lst, int fd);
void		*ft_memcpy(void *dest, const void *src, size_t len);
char		*ft_lf_check(char *line, size_t len, t_fileinfo *fi);
char		*ft_append_line(char *line, ssize_t len, int t, t_fileinfo *fi);
char		*ft_read_line(int fd, t_fileinfo *fi, t_list **lst);
char		*ft_clean_up(char *line, t_fileinfo *fi, t_list **lst);

#endif
