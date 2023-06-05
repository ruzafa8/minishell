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

/**
 * TODO: tener en cuenta que me pongan """""""""      " """""" 54 "          " 
 * 		 y que ponga el numero????
**/
int	built_in_exit(t_command *command, t_shell_data *data)
{
	int	code;

	(void)data;
	ft_printf("exit\n");
	code = ft_atoi(command->argv[1]);
	exit(code);
}
