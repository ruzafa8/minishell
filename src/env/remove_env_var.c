/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:29:26 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 20:29:46 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @return -1 si no existe en el env.
 */
int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

/**
 * @return el env nuevo o NULL si falla el malloc.
 */
static char	**realloc_env_vars(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(new_env));
	if (!new_env)
		return (0);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

/**
 * Añade la variable al env.
 *
 * si ya existe, le cambia el valor
 * si no, crea una nueva.
 *
 * @return 1 si ha ocurrido,
 * 0 si se ha destruido.
 */
int	set_env_var(t_shell_data *data, char *key, char *value)
{
	int		idx;
	char	*aux;

	idx = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, aux);
	}
	else
	{
		idx = env_size(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
			return (12);
		data->env[idx] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}

/**
 * borra la variable del env en la posicion "idx"
 *
 * @return 1 si ha ocurrido,
 * 0 si el idx es invalido o falla con el malloc
 */
int	remove_env_var(t_shell_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_size(data->env))
		return (0);
	free_ptr(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env_vars(data, count);
	if (!data->env)
		return (0);
	return (1);
}
