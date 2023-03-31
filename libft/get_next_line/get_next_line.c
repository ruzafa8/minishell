/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:25:20 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/28 18:34:00 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_search_eol(char *buffer, int *at)
{
	int	i;

	i = 0;
	while (*buffer)
	{
		if (*buffer == '\n')
		{
			*at = i;
			return (1);
		}
		i++;
		buffer++;
	}
	return (0);
}

static int	ft_read_and_split(int fd, char *buffer, char **line, int *eol_idx)
{
	int		b_read;
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = 0;
	b_read = read(fd, buffer, BUFFER_SIZE);
	if (b_read == -1)
		return (-1);
	if (ft_search_eol(buffer, eol_idx))
		gnl_strjoin(line, buffer, ((size_t)(*eol_idx)) + 1);
	else
	{
		gnl_strjoin(line, buffer, ft_strlen(buffer));
		*eol_idx = -1;
	}
	return (b_read);
}

static int	ft_revise_memory(char **st_mem, char **res)
{
	int		at;
	char	*aux;

	if (!*st_mem)
	{
		*res = 0;
		return (0);
	}
	if (ft_search_eol(*st_mem, &at))
	{
		*res = ft_substr(*st_mem, 0, at + 1);
		aux = *st_mem;
		*st_mem = ft_substr(aux, at + 1, ft_strlen(*st_mem));
		free(aux);
		return (1);
	}
	else
	{
		*res = ft_strdup(*st_mem);
		free(*st_mem);
		*st_mem = 0;
		return (0);
	}
}

static char	*process(int fd, char *buffer, char **static_memory)
{
	int		b_read;
	int		eol_idx;
	char	*res;

	if (ft_revise_memory(static_memory, &res))
		return (res);
	b_read = 1;
	while (b_read)
	{
		b_read = ft_read_and_split(fd, buffer, &res, &eol_idx);
		if (b_read == -1 || !res)
			return (0);
		if (eol_idx != -1)
		{
			free(*static_memory);
			*static_memory = ft_substr(buffer,
					((size_t) eol_idx) + 1, ft_strlen(buffer));
			return (res);
		}
	}
	free(*static_memory);
	static_memory = 0;
	gnl_strjoin(&res, buffer, ft_strlen(buffer));
	return (res);
}

char	*ft_get_next_line(int fd)
{
	char		*res;
	static char	*static_memory;
	char		*buffer;

	if (BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	res = process(fd, buffer, &static_memory);
	free(buffer);
	return (res);
}
