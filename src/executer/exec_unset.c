/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:23:30 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:23:41 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_infinite_vars(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	int		idxenv;
	int		idxexp;

	i = 1;
	args = command->argv;
	while (i < command->argc)
	{
		idxenv = get_env_var_index(data->env, args[i]);
		idxexp = get_env_var_index(data->exportenv, args[i]);
		if (idxenv != -1)
			remove_env_var(data, idxenv);
		if (idxexp != -1)
			remove_exportenv_var(data, idxexp);
		i++;
	}
}

int	built_in_unset(t_command *command, t_shell_data *data)
{
	if (command->argc == 1)
		;
	else if (command->argc > 1)
		unset_infinite_vars(command, data);
	return (0);
}
