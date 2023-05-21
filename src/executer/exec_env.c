



#include "minishell.h"

int	built_in_env(t_command *command, t_shell_data *data)
{
	int		res_code;
	char	**envaux;
	int		i;

	res_code = 0; //NOSESABELOQUEHAYQUEHACERAHORAMISMO
	i = 0;
	envaux = data->env;
	if (command->argc == 1)
	{
		while (i < env_size(envaux))
		{
			printf("%s\n",envaux[i]);
			i++;
		}
	}
	else
	{
		ft_printf("Error, env built in doesnt support any args or flags\n");
		res_code = 7; // nosecomomanejamosloserrorestodavia
	}
	return (res_code);
}