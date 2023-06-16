/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:16:38 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:29:47 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_env(t_command *command, t_shell_data *data)
{
	int		res_code;
	char	**envaux;
	int		i;

	res_code = 0;
	i = 0;
	envaux = data->env;
	if (command->argc == 1)
	{
		while (i < env_size(envaux))
		{
			printf("%s\n", envaux[i]);
			i++;
		}
	}
	else
		return (print_error("env", 0,
				"Error, env built in doesnt support any arguments or flags",
				1));
	return (res_code);
}
