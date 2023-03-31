/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:36:41 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/02/25 15:57:32 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*concat_slash(char *c)
{
	char	*res;
	size_t	len;

	len = ft_strlen(c);
	res = (char *) ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (0);
	ft_memcpy(res, c, len);
	res[len] = '/';
	return (res);
}

static char	**compute_path(char *arg)
{
	size_t	i;
	char	*aux;
	char	**res;

	i = 0;
	res = ft_split(arg, ':');
	if (!res)
		return (0);
	while (res[i])
	{
		aux = concat_slash(res[i]);
		free(res[i]);
		res[i] = aux;
		i++;
	}
	return (res);
}

static char	**free_args(char	**arg)
{
	if (!arg)
		return (0);
	if (arg[0] != 0)
		free(arg[0]);
	if (arg[1] != 0)
		free(arg[1]);
	free(arg);
	return (0);
}

char	**px_get_path(char **env)
{
	char	**arg;
	char	**res;

	while (env)
	{
		arg = ft_split(*env, '=');
		if (!arg || !arg[0] || !arg[1])
			return (free_args(arg));
		if (ft_strncmp(arg[0], "PATH", 4) == 0)
		{
			res = compute_path(arg[1]);
			free_args(arg);
			return (res);
		}
		else
			free_args(arg);
		env++;
	}
	return (0);
}

void	px_free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
