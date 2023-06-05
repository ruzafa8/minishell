/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:01:35 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 20:23:43 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Devuelve el enviroment actualizado con la variable eliminada.
 * 
 * @param data: estructura de datos.
 * @param size: número de variables del nuevo env.
 * @return el env nuevo o NULL si falla el malloc.
 * 
 * TODO: Ese sizeof * new_env no es correcto.
 */
static char	**realloc_export_env_vars(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (0);
	i = 0;
	while (data->exportenv[i] && i < size)
	{
		new_env[i] = ft_strdup(data->exportenv[i]);
		free_ptr(data->exportenv[i]);
		i++;
	}
	free(data->exportenv);
	return (new_env);
}

int	set_export_env_var(t_shell_data *data, char *key, char *value)
{
	int		idx;
	char	*aux;

	idx = get_env_var_index(data->exportenv, key);
	if (!value)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (idx != -1 && data->exportenv[idx])
	{
		free_ptr(data->exportenv[idx]);
		data->exportenv[idx] = ft_strjoin(key, aux);
	}
	else
	{
		idx = env_size(data->exportenv);
		data->exportenv = realloc_export_env_vars(data, idx + 1);
		if (!data->exportenv)
			return (12);
		data->exportenv[idx] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}
