#include "minishell.h"

/**
 * This function deletes any command node.
 */
void	free_command(t_command_old *command)
{
	if (!command)
		return ;
	if (command->type == CD)
		free_cd(command->data);
	free(command);
}