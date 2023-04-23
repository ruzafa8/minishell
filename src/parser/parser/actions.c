


#include "minishell.h"

t_pars_err	pars_set_stdin(t_list *commands, char *filename)
{
	t_command	*command;

	command = (t_command *) ft_lstlast(commands)->content;
	command->fd_in = open(filename, O_RDONLY);
	if (command->fd_in == -1)
		return (PARS_NO_SUCH_FILE_OR_DIR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_set_stdout(t_list *commands, char *filename, int append)
{
	t_command	*command;
	int			permissions;
	int			mode;

	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mode = O_WRONLY | O_CREAT | O_TRUNC;
	if (append)
		mode = O_WRONLY | O_CREAT | O_APPEND;
	command = (t_command *) ft_lstlast(commands)->content;
	command->fd_out = open(filename, mode, permissions);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_append_arg_to_command(t_list *commands, char *value)
{
	t_command	*command;
	char		**new_argv;
	int			i;

	command = (t_command *) ft_lstlast(commands)->content;
	new_argv = (char **) ft_calloc(command->argc + 2, sizeof(char *));
	if (!new_argv)
		return (PARS_MALLOC_ERROR);
	i = 0;
	while (command->argv[i])
	{
		new_argv[i] = command->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(value);
	if (!new_argv[i])
		return (PARS_MALLOC_ERROR);
	command->argc++;
	free(command->argv);
	command->argv = new_argv;
	return (PARS_NO_ERROR);
}

t_pars_err	pars_append_new_command(t_list **commands, char *value)
{
	t_command	*command;

	command = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!command)
		return (PARS_MALLOC_ERROR);
	command->argv = (char **) ft_calloc(2, sizeof(char *));
	if (!command->argv)
		return (PARS_MALLOC_ERROR);
	if (value)
	{
		command->argv[0] = ft_strdup(value);
		if (!command->argv[0])
			return (PARS_MALLOC_ERROR);
		command->argc = 1;
	}
	ft_lstadd_back(commands, ft_lstnew(command));
	return (PARS_NO_ERROR);
}
