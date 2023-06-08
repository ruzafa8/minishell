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

static int	esnum(char *str)
{
	int	i;
	int	is;

	i = 0;
	is = 1;
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

	(void)data;
	if (command->argc > 2)
	{
		if(!esnum(command->argv[1]))
		{
			ft_printf("exit\nminishell: exit: %s: numeric argument required",command->argv[1]);
			return (255);
		}
		return (ft_printf("exit\nminishell: exit: too many arguments"),1);
	}
	if(!esnum(command->argv[1]))
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required",command->argv[1]);
		return (255);
	}

	else if (command->argc == 1)
		return (ft_printf("exit\n"),0);
	else
	{
		ft_printf("exit\n");
		code = ft_atoi(command->argv[1]);
		exit(code);
	}
	return 0;
}
