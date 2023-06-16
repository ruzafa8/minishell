/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:35:27 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 20:17:00 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitshell(t_shell_data *data, int exitcode)
{
	if (data)
	{
		free_envs(data);
		ft_lstclear(&data->commands, del_t_command);
		if (data->dup_stdin)
			close(data->dup_stdin);
		if (data->dup_stdout)
			close(data->dup_stdout);
		free(data);
	}
	exit(exitcode);
}

static int	esnum(char *str)
{
	int	i;
	int	is;

	i = 0;
	is = 1;
	if (!str)
		return (0);
	while (str[i] && is)
	{
		is = ft_isdigit(str[i]);
		i++;
	}
	return (is);
}

int	built_in_exit(t_command *command, t_shell_data *data)
{
	int	code;

	ft_printf("exit\n");
	if (command->argc > 2)
	{
		if (!esnum(command->argv[1]))
			exitshell(data,
				print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if (!esnum(command->argv[1]) && command->argc > 1)
		exitshell(data,
			print_error("exit", 0, "numeric argument required", 255));
	else if (command->argc == 1)
		exitshell(data, 0);
	else
	{
		code = ft_atoi(command->argv[1]) % 256;
		exitshell(data, code);
	}
	return (255);
}
