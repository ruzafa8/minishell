#include "minishell.h"

int	main(int argc, char **args, char **env)
{
	(void)argc;
	(void)args;
	t_shell_data	*shell_data;

	shell_data = init_shell_data(env);
	loop_shell(shell_data);
	return (0);
}