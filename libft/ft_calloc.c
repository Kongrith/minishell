/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvesterl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:38:42 by rvesterl          #+#    #+#             */
/*   Updated: 2024/08/29 08:04:46 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	else if ((size_t)(SIZE_MAX - 1) / nmemb < size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem)
		ft_bzero(mem, nmemb * size);
	return (mem);
}
