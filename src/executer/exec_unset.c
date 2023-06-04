


#include "minishell.h"

int	built_in_unset(t_command *command, t_shell_data *data)
{
	char	**export_env_aux;

	export_env_aux = data->exportenv;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		set_infinite_vars(command, data);
	return (0);
}