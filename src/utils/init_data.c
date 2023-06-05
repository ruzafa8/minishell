/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:47:17 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:40:50 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/**
 * Función que inicializa el env.
 * @return 1 si todo ha ido bien, 0 si ha habido algún error.
 * 
 * TODO: Revisar leaks. Hay que liberar el exportenv en el while si
 * hay algún error.
 */
int	init_env(t_shell_data *aux, char **env)
{
	int	i;

	i = 0;
	aux->env = ft_calloc(env_size(env) + 1, sizeof(aux->env));
	if (!aux->env)
		return (0);
	while (env[i])
	{
		aux->env[i] = ft_strdup(env[i]);
		if (!aux->env[i])
			return (0);
		i++;
	}
	return (1);
}

/**
 * Función que inicializa el export env.
 * @return 1 si todo ha ido bien, 0 si ha habido algún error.
 * 
 * TODO: Revisar leaks. Hay que liberar el exportenv en el while si
 * hay algún error.
 */
int	init_export_env(t_shell_data *aux, char **env)
{
	int	i;

	i = 0;
	aux->exportenv = ft_calloc(env_size(env) + 1, sizeof(aux->env));
	if (!aux->exportenv)
		return (0);
	while (env[i])
	{
		aux->exportenv[i] = ft_strdup(env[i]);
		if (!aux->exportenv[i])
			return (0);
		i++;
	}
	return (1);
}

t_shell_data	*init_shell_data(char **env)
{
	t_shell_data	*aux;

	aux = (t_shell_data *)ft_calloc(1, sizeof(t_shell_data));
	init_env(aux, env);
	init_export_env(aux, env);
	return (aux);
}
