/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:15:28 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/16 13:10:20 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_format(const char *str, t_pformat *pf)
{
	t_list	*lst_tmp;
	char	*seg;
	size_t	pos;
	size_t	start_pos;

	pos = 0;
	start_pos = 0;
	lst_tmp = ft_lstnew(NULL);
	pf->lst_seg = lst_tmp;
	while (str[pos] != '\0')
	{
		pos = ft_conv_pos(str, pos);
		seg = ft_substr(str, start_pos, pos - start_pos);
		if (pf->lst_seg->content == NULL)
			pf->lst_seg->content = seg;
		else
		{
			lst_tmp = ft_lstnew(seg);
			ft_lstadd_back(&pf->lst_seg, lst_tmp);
		}
		start_pos = pos;
	}
	return ;
}

static void	*set_format_content(void *content, t_pformat *pf)
{
	char	*cstr;
	t_cont	*cs;
	size_t	str_len;

	cs = malloc(sizeof(t_cont) * 1);
	if (!cs)
		return (NULL);
	cstr = (char *) content;
	str_len = ft_strlen(cstr);
	if (cstr[0] != '%' || (str_len != 2 && !ft_is_conv(cstr[1])))
	{
		pf->tot_len += str_len;
		cs->len = str_len;
		cs->seg = ft_strdup(cstr);
		return (cs);
	}
	ft_conversion(1, cstr, cs, pf);
	pf->tot_len += cs->len;
	return (cs);
}

static int	set_format(t_pformat *pf)
{
	pf->tot_len = 0;
	pf->lst_res = ft_lstmap_pf(pf->lst_seg, pf, set_format_content, \
		del_lst_res_content);
	if (!pf->lst_res)
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	t_pformat	pf;

	if (!str)
		return (-1);
	if (ft_strlen(str) == 0)
		return (0);
	va_start(pf.varg, str);
	parse_format(str, &pf);
	if (!set_format(&pf))
	{
		va_end(pf.varg);
		return (-1);
	}
	ft_lstiter(pf.lst_res, print_lst_seg);
	ft_lstclear(&pf.lst_seg, del_lst_seg_content);
	ft_lstclear(&pf.lst_res, del_lst_res_content);
	va_end(pf.varg);
	return (pf.tot_len);
}
