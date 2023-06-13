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
		ft_lstclear(&data->commands, del_t_command);//HAY QUE HACER UNO NUEVO??? EL DELONE O QUE PASA
		if (data->dup_stdin)
			close(data->dup_stdin);//alomejor esto sobra
		if (data->dup_stdout)
			close(data->dup_stdout);//alomejor esto sobra
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



/**
 * TODO: tener en cuenta que me pongan """""""""      " """""" 54 "          " 
 * 		 y que ponga el numero????
 * 
 * TODO: en el controlD poner que haga exit en el handle
 * 
 * TODO: modulo 256 los errores pa que rente num%256
**/
int	built_in_exit(t_command *command, t_shell_data *data)
{
	int	code;

	if (command->argc > 2)
	{
		if(!esnum(command->argv[1]))
			exitshell(data, print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if(!esnum(command->argv[1]) && command->argc > 1)
		exitshell(data, print_error("exit", 0, "numeric argument required", 255));
	else if (command->argc == 1)
	{	
		ft_printf("exit\n");
		exitshell(data, 0);
	}
	else
	{
		ft_printf("exit\n");
		code = ft_atoi(command->argv[1]) % 256;
		exitshell(data, code);
	}
	return (255);
}
