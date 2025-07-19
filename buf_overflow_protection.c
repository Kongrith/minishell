/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_overflow_protection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:20:29 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/02 07:37:40 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resize_heap_memory(char *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	old_size;
	size_t	bytes_to_copy;

	old_size = ft_strlen(ptr) + 1;
	if (ptr == NULL)
		return ((char *)malloc(new_size * sizeof(char)));
	if (new_size <= 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = (char *)malloc(new_size * sizeof(char));
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		bytes_to_copy = old_size;
	else
		bytes_to_copy = new_size;
	ft_memcpy(new_ptr, ptr, bytes_to_copy);
	free(ptr);
	return (new_ptr);
}

static int	eval_bytes(char **ptr, size_t new_size)
{
	size_t	old_size;
	size_t	bytes_to_copy;

	old_size = count_pointer_to_array(ptr) + 1;
	if (old_size < new_size)
		bytes_to_copy = old_size;
	else
		bytes_to_copy = new_size;
	return (bytes_to_copy);
}

static char	**resize_double_ptr(char **ptr, size_t new_size)
{
	char	**new_ptr;
	size_t	bytes_to_copy;
	size_t	i;

	if (ptr == NULL)
		return ((char **)malloc(new_size * sizeof(char *)));
	if (new_size <= 0)
	{
		if (ptr)
			free_double_ptr(ptr);
		return (NULL);
	}
	new_ptr = (char **)ft_calloc(new_size, sizeof(char *));
	if (!new_ptr)
		return (NULL);
	bytes_to_copy = eval_bytes(ptr, new_size);
	i = 0;
	while (i < bytes_to_copy && ptr[i])
	{
		new_ptr[i] = ft_calloc(ft_strlen(ptr[i]) + 1, sizeof(char));
		ft_strcpy(new_ptr[i], ptr[i]);
		i++;
	}
	new_ptr[i] = NULL;
	return (new_ptr);
}

void	dynamic_token_size(char **token, char *str, char *tmp)
{
	char	*new_token;

	if (ft_strlen(tmp) + ft_strlen(*token) > ft_strlen(str))
	{
		new_token = (char *)resize_heap_memory(*token, \
(ft_strlen(tmp) + ft_strlen(*token) + 1) * sizeof(char));
		*token = new_token;
	}
}

void	dynamic_segment_size(char ***tokens, int *token_size, int j)
{
	char	**new_tokens;

	if (j + 2 >= *token_size)
	{
		while (*token_size < j + 2)
			*token_size += TOKEN_SIZE;
		new_tokens = (char **)resize_double_ptr(*tokens, *token_size);
		if (*tokens)
			free_double_ptr(*tokens);
		*tokens = new_tokens;
	}
}
