



#include "minishell.h"

static void	free_args(char **arg)
{
	if (!arg)
		return ;
	if (arg[0] != 0)
		free(arg[0]);
	if (arg[1] != 0)
		free(arg[1]);
	free(arg);
}


static void print_export_env(t_shell_data *data)
{
	char	**export_env_aux;
	int		i;
	char	**iterator;

	i = 0;
	export_env_aux = data->exportenv;
	while (i < env_size(export_env_aux))
	{
		iterator = ft_split(export_env_aux[i], '=');
		printf("declare -x %s=\"%s\"\n", iterator[0], iterator[1]); //declare -x VARIABLE="valor"\n
		free_args(iterator);
		i++;
	}
}
/*
	caracteres invalidos de variable:
	
	"ñç:-!¡·¢$/?¿+^¨ÑÇ.,"
	
	cualquier numero en la primera posicion de la variable, si es en la segunda le gusta

*/
static int	is_valid_name(char *arg)
{
	char	*invalid_chars;
	int		i;
	int		is_valid;
	char	**splitted;

	i = 0;
	is_valid = 1;
	invalid_chars = "ñç:-!¡·¢$/?¿+^¨ÑÇ.,";
	if (arg[0] == '=')
		return (0);
	splitted = ft_split(arg, '=');
	while ((i < ft_strlen(invalid_chars)) && (is_valid == 1))
	{
		if (!ft_strchr(arg, invalid_chars[i]))
			is_valid = 0;
		i++;
	}
	if (is_valid == 0)


	free_args(splitted);
}

static void set_infinite_vars(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;

	i = 1;
	args = command->argv;
	while (i < command->argc)
	{
		if (is_valid_name(args[i]))

		i++;
	}
}

	//QUE PASA SI PONGO MUCHAS SEGUIDAS??
	//EL ENV DEL EXPORT hay que hacerlo si o si
	//COÑAZO GRANDE, SI PONES UNA 'ñ' EN EL NOMBRE DE UNA VARIABLE DEBERIA DE FALLAR ¿¿¿¿¿o si pones '_'???? ((ft_isprint))
int	built_in_export(t_command *command, t_shell_data *data)
{
	int		res_code;
	char	**export_env_aux;
	int		i;

	res_code = 0; //NOSESABELOQUEHAYQUEHACERAHORAMISMO
	i = 0;
	export_env_aux = data->exportenv;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		set_infinite_vars(command, data);
	else
	{
		ft_printf("Error, env built in doesnt support any args or flags\n");
		res_code = 7; // nosecomomanejamosloserrorestodavia
	}
	return (res_code);
}
