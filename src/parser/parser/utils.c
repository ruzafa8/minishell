

#include "minishell.h"

static void	free_node(void *node)
{
	t_command	*command;
	int			i;

	if (!node)
		return ;
	command = (t_command *) node;
	i = 0;
	while (command->argv[i])
	{
		ft_printf("About to delete: %s.\n", command->argv[i]);
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	free(command);
}

void	pars_free_command_list(t_list **cmds)
{
	if (!cmds)
		return ;
	ft_lstclear(cmds, &free_node);
}
