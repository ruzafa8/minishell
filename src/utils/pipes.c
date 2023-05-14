#include "minishell.h"

static void	iterate_to_close(t_list *current, t_list *next, t_list *commands)
{
	while (commands)
	{
		if (commands == current)
		{
			if (((t_command *)commands->content)->fd_in > 0)
				close(((t_command *)commands->content)->fd_in);
		}
		else if (next && commands == next)
		{
			if (((t_command *)commands->content)->fd_out > 0)
				close(((t_command *)commands->content)->fd_out);
		}
		else
		{
			if (((t_command *)commands->content)->fd_in > 0)
				close(((t_command *)commands->content)->fd_in);
			if (((t_command *)commands->content)->fd_out > 0)
				close(((t_command *)commands->content)->fd_out);
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
