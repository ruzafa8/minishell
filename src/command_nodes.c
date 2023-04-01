/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:10:14 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/04/01 22:36:12 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * This function creates a CD command node.
 * @param path path to send to cd built-in.
 * @returns A pointer to the node or NULL if any allocation problem.
 */
t_command	*create_cd(char *path)
{
	t_command	*res;

	res = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!res)
		return (0);
	res->data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!res->data)
		return (free(res), 0);
	res->type = CD;
	res->data->cd = (t_cd *) ft_calloc(1, sizeof(t_cd));
	if (!res->data->cd)
		return (free_cd(res->data), free(res), 0);
	res->data->cd->path = ft_strdup(path);
	// TODO: Es necesario esto? Podría llegarme un path NULL?
	if (!res->data->cd->path)
		return (free_cd(res->data), free(res), 0);
	return (res);
}

/**
 * This function makes a free of a CD node.
 * @param data A pointer to the CD node to free.
 */
void	*free_cd(t_data	*data)
{
	if (data)
	{
		if (data->cd)
		{
			if (data->cd->path)
				free(data->cd->path);
			free(data->cd);
		}
		free(data);
	}
}

/**
 * This function creates a GENERIC command node.
 * @param command command to send to execve the found command.
 * @param full_command command with parameters to send to execve the found command.
 * @returns A pointer to the node or NULL if any allocation problem.
 */
t_command	*create_generic(char *command, char **full_command)
{
	t_command	*res;

	res = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!res)
		return (0);
	res->type = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!res->type)
		return (free(res), 0);
	res->type = GENERIC;
	res->data->generic = (t_generic *) ft_calloc(1, sizeof(t_generic));
	if (!res->data->generic)
		return (free(res), 0);
	res->data->generic->command = ft_strdup(command);
	// TODO: Es necesario esto? Podría llegarme un command NULL?
	if (!res->data->generic->command)
		return (free(res), 0);
	res->data->generic->full_command = full_command;
	// TODO: Es necesario esto? Podría llegarme un full_command NULL?
	if (!res->data->generic->full_command)
		return (free(res), 0);
	return (res);
}

/**
 * This function deletes any command node.
 */
void	*free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->type == CD)
		free_cd(command->data);
	free(command);
}