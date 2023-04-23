#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	t_shell_data	*shell_data;

	shell_data = init_shell_data(env);
	if (argc == 1)
		loop_shell(shell_data);//es de ser interactiva
	else if (ft_strncmp(argv[1], "-c", 3) == 0)
		write(1,"usted gracas",12);//cero de ser interactiva
	return (0);
}