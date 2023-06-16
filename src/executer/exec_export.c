/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:20:28 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:22:17 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	print_export_env(t_shell_data *data)
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
			printf("declare -x %s\n", iterator[0]);
		else
			printf("declare -x %s=\"%s\"\n", iterator[0], iterator[1]);
		free_args(iterator);
		i++;
	}
}

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
		return (0);
	splitted = ft_split(arg, '=');
	while (((i < (int)ft_strlen(splitted[0]))) && (is_valid == 1))
	{
		if (ft_strchr(invalid_chars, splitted[0][i])
			|| ft_isdigit(splitted[0][0]))
			is_valid = 0;
		i++;
	}
	free_args(splitted);
	return (is_valid);
}

/*
	si es la variable tal cual sin el = SOLO SE GUARDA EN EL EXPORT 
	si es la variable con el = se guarda en el env y el export con cadena vacia
	en otro caso se guarda en el env y el export con los valores y ya

*/
static int	set_infinite_vars(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	char	**splited;

	i = 0;
	args = command->argv;
	while (++i < command->argc)
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
		else
			return (print_error("export", args[i], "not a valid identifier",
					1));
	}
	return (0);
}

int	built_in_export(t_command *command, t_shell_data *data)
{
	int	rescode;

	rescode = 0;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		rescode = set_infinite_vars(command, data);
	return (rescode);
}
