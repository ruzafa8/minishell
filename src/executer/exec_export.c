



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
		if (!iterator[1])
			printf("declare -x %s\n", iterator[0]); //declare -x VARIABLE\n
		else
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
	invalid_chars = ":-!/?+^.,";
	if (arg[0] == '=')
		return (ft_printf("minishell: export: \'=\': not a valid identifier\n"), 0);
	splitted = ft_split(arg, '=');
	while (((i < (int)ft_strlen(splitted[0]))) && (is_valid == 1))
	{
		if (ft_strchr(invalid_chars, splitted[0][i]) || ft_isdigit(splitted[0][0]))
			is_valid = 0;
		i++;
	}
	if (is_valid == 0)
		ft_printf("minishell: export: \'%s\': not a valid identifier\n", splitted[0]);
	free_args(splitted);
	return (is_valid);
}

/*
	si es la variable tal cual sin el = SOLO SE GUARDA EN EL EXPORT 
	si es la variable con el = se guarda en el env y el export con cadena vacia
	en otro caso se guarda en el env y el export con los valores y ya

*/
static void set_infinite_vars(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	char	**splited;

	i = 1;
	args = command->argv;
	while (i < command->argc)
	{
		if (is_valid_name(args[i]))
		{
			if (!ft_strchr(args[i], '='))
				set_export_env_var(data, args[i], "");
			else
			{
				splited = ft_split(args[i], '=');
				set_env_var(data, splited[0], splited[1]);
				set_export_env_var(data, splited[0], splited[1]);
				free_args(splited);
			}
		}
		i++;
	}
}

int	built_in_export(t_command *command, t_shell_data *data)
{
	char	**export_env_aux;

	export_env_aux = data->exportenv;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		set_infinite_vars(command, data);
	return (0);
}
