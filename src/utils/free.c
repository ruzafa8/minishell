/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:46:56 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:32:34 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_envs(t_shell_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free_ptr(data->env[i]);
		i++;
	}
	free_ptr(data->env);
	i = 0;
	while (data->exportenv[i])
	{
		free_ptr(data->exportenv[i]);
		i++;
	}
	free_ptr(data->exportenv);
}

void	del_t_command(void *com)
{
	t_command	*command;
	int			i;

	command = (t_command *) com;
	close(command->fd_in);
	close(command->fd_out);
	i = 0;
	while (command->argv[i])
	{
		free_ptr(command->argv[i]);
		i++;
	}
	free_ptr(command->argv);
}
