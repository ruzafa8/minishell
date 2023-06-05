/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:44:30 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:39:41 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		aux = ft_strjoin(res[i], "/");
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

char	**get_path(char **env)
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

void	free_path(char **path)
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
