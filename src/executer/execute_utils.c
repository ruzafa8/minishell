/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:26:45 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/06 18:31:22 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	decode_error(int err)
{
	int	res;

	res = 1;
	if (WIFEXITED(err))
		res = WEXITSTATUS(err);
	return (res);
}

int	is_builtin(char *command)
{
	return (ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "env", 4) == 0
		|| ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "exit", 5) == 0
		|| ft_strncmp(command, "echo", 5) == 0);
}

int	execute_builtins(t_command *command, t_shell_data *data)
{
	int	status;

	status = 0;
	if (ft_strncmp(command->argv[0], "cd", 3) == 0)
		status = built_in_cd(command, data);
	else if (ft_strncmp(command->argv[0], "env", 4) == 0)
		status = built_in_env(command, data);
	else if (ft_strncmp(command->argv[0], "export", 7) == 0)
		status = built_in_export(command, data);
	else if (ft_strncmp(command->argv[0], "unset", 6) == 0)
		status = built_in_unset(command, data);
	else if (ft_strncmp(command->argv[0], "exit", 5) == 0)
		status = built_in_exit(command, data);
	else if (ft_strncmp(command->argv[0], "echo", 5) == 0)
		status = built_in_echo(command);
	return (status);
}
