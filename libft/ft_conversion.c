/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:16:22 by rvesterl          #+#    #+#             */
/*   Updated: 2024/09/16 13:34:28 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	conversion1(size_t i, char *cstr, t_cont *cs, t_pformat *pf)
{
	char	*tmp;

	if (cstr[i] == 'c')
	{
		tmp = ft_strdup(" ");
		if (!tmp)
			return ;
		tmp[0] = (char) va_arg(pf->varg, int);
		cs->seg = tmp;
		cs->len = 1;
	}
	else if (cstr[i] == 's')
	{
		tmp = va_arg(pf->varg, char *);
		if (tmp == NULL)
			cs->seg = ft_strdup("(null)");
		else
			cs->seg = ft_strdup(tmp);
		cs->len = ft_strlen(cs->seg);
	}
}

static void	p_string_copy(t_cont *cs, char *tmp1, char *tmp2)
{
	if (!tmp2)
		tmp2 = ft_strdup("");
	if (!tmp1 || !tmp2)
		return ;
	cs->len = ft_strlen(tmp1) + ft_strlen(tmp2) + ft_strlen(HEX_PREFIX);
	cs->seg = ft_calloc((cs->len + 1), sizeof(char));
	ft_strlcpy(cs->seg, HEX_PREFIX, 3);
	ft_strlcat(cs->seg, tmp1, cs->len + 1);
	free(tmp1);
	ft_strlcat(cs->seg, tmp2, cs->len + 1);
	free(tmp2);
}

static void	conversion2(size_t i, char *cstr, t_cont *cs, t_pformat *pf)
{
	char				*tmp1;
	char				*tmp2;
	void				*vp;
	unsigned long long	n;

	tmp2 = NULL;
	if (cstr[i] == 'p')
	{
		vp = va_arg(pf->varg, void *);
		if (!vp)
		{
			cs->seg = ft_strdup("(nil)");
			cs->len = 5;
			return ;
		}
		n = (unsigned long long) vp;
		if (n >= 16)
		{
			tmp1 = ft_putnbr_base(n / 16, HEX_C_L);
			tmp2 = ft_putnbr_base(n % 16, HEX_C_L);
		}
		else
			tmp1 = ft_putnbr_base(n % 16, HEX_C_L);
		p_string_copy(cs, tmp1, tmp2);
	}
}

static void	conversion3(size_t i, char *cstr, t_cont *cs, t_pformat *pf)
{
	if (cstr[i] == 'd' || cstr[i] == 'i')
		cs->seg = ft_putnbr_base(va_arg(pf->varg, int), DEC_C);
	else if (cstr[i] == 'u')
		cs->seg = ft_putnbr_base(va_arg(pf->varg, unsigned int), DEC_C);
	else if (cstr[i] == 'X')
		cs->seg = ft_putnbr_base(va_arg(pf->varg, unsigned int), HEX_C_U);
	else if (cstr[i] == 'x')
		cs->seg = ft_putnbr_base(va_arg(pf->varg, unsigned int), HEX_C_L);
	else if (cstr[i] == '%')
		cs->seg = ft_strdup("%");
	cs->len = ft_strlen(cs->seg);
}

void	ft_conversion(size_t i, char *cstr, t_cont *cs, t_pformat *pf)
{
	cs->seg = NULL;
	conversion1(i, cstr, cs, pf);
	if (!cs->seg)
		conversion2(i, cstr, cs, pf);
	if (!cs->seg)
		conversion3(i, cstr, cs, pf);
}
