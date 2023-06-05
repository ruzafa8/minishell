/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:22:01 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 20:22:42 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_expenv_vars(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(new_env));
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

/**
 * Borra la variable del exportenv en la posicion "idx"
 *
 * @return 1 si ha ocurrido,
 * 0 si el idx es invalido o falla con el malloc
 */
int	remove_exportenv_var(t_shell_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_size(data->exportenv))
		return (0);
	free_ptr(data->exportenv[idx]);
	i = idx;
	count = idx;
	while (data->exportenv[i + 1])
	{
		data->exportenv[i] = ft_strdup(data->exportenv[i + 1]);
		free_ptr(data->exportenv[i + 1]);
		count++;
		i++;
	}
	data->exportenv = realloc_expenv_vars(data, count);
	if (!data->exportenv)
		return (0);
	return (1);
}
