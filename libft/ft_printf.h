/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:01:46 by rvesterl          #+#    #+#             */
/*   Updated: 2025/05/01 13:52:05 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

# define HEX_C_U "0123456789ABCDEF"
# define HEX_C_L "0123456789abcdef"
# define DEC_C "0123456789"
# define HEX_PREFIX "0x"

typedef struct s_pformat
{
	va_list	varg;
	t_list	*lst_seg;
	t_list	*lst_res;
	size_t	tot_len;
}	t_pformat;

typedef struct s_cont
{
	char	*seg;
	size_t	len;
}	t_cont;

int		ft_printf(const char *str, ...)
		__attribute__ ((format (printf, 1, 2)));
char	*ft_putnbr_base(long lnbr, char *base);
t_list	*ft_lstmap_pf(t_list *lst, t_pformat *pf,
			void *(*f)(void *, t_pformat *), void (*del)(void *));
size_t	ft_conv_pos(const char *str, size_t pos);
void	ft_conversion(size_t i, char *cstr, t_cont *cs, t_pformat *pf);
void	print_lst_seg(void *lst_content);
void	del_lst_seg_content(void *lst_content);
void	del_lst_res_content(void *lst_content);
int		ft_is_conv(char c);

#endif
