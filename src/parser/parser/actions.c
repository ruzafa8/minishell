


#include "minishell.h"

void	pars_append_arg_to_command(t_list *commands, char *value)
{
	t_command	*command;
	char		**new_argv;
	int			i;

	command = (t_command *) ft_lstlast(commands)->content;
	new_argv = (char **) ft_calloc(command->argc + 2, sizeof(char *));
	i = 0;
	while (command->argv[i])
	{
		new_argv[i] = ft_strdup(command->argv[i]);
		i++;
	}
	new_argv[i] = ft_strdup(value);
	command->argc++;
	free(command->argv);
	command->argv = new_argv;
}

void	pars_append_new_command(t_list **commands, char *value)
{
	t_command	*command;

	command = (t_command *) ft_calloc(1, sizeof(t_command));
	command->argv = (char **) ft_calloc(2, sizeof(char *));
	if (value)
	{
		command->argv[0] = ft_strdup(value);
		command->argc = 1;
	}
	ft_lstadd_back(commands, ft_lstnew(command));
}
