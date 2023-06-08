/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:49:39 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/08 18:14:42 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

static void	iterate_to_close(t_list *current, t_list *next, t_list *commands)
{
	t_command	*command;

	while (commands)
	{
		command = (t_command *) commands->content;
		if (commands == current)
			close_fd(command->fd_in);
		else if (next && commands == next)
			close_fd(command->fd_out);
		else
		{
			close_fd(command->fd_in);
			close_fd(command->fd_out);
		}
		commands = commands->next;
	}
}

/**
 * Closes all pipes except the ones that are needed for the current
 * instruction.
 */
void	close_pipes(t_shell_data *data, t_list *instr)
{
	t_list	*current;
	t_list	*next;
	t_list	*commands;

	commands = data->commands;
	next = 0;
	current = 0;
	if (instr)
		current = instr->content;
	if (instr && instr->next)
		next = instr->next->content;
	iterate_to_close(current, next, commands);
}
