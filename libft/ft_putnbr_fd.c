/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:07:41 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/30 14:33:42 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	lnbr;

	lnbr = n;
	if (lnbr < 0)
	{
		write(fd, "-", 1);
		lnbr = -lnbr;
	}
	if (lnbr >= 10)
	{
		ft_putnbr_fd(lnbr / 10, fd);
		ft_putchar_fd(lnbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(lnbr + '0', fd);
}
