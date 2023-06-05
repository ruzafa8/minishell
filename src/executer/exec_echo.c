/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:15:24 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:16:15 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printmatrix(char **aux)
{
	int	i;

	i = 1;
	while (aux[i])
	{
		ft_printf("%s", aux[i]);
		if (aux[i + 1])
			ft_printf(" ");
		i++;
	}
}

static void	printmatrix_n(char **aux)
{
	int	i;

	i = 2;
	while (aux[i])
	{
		ft_printf("%s", aux[i]);
		if (aux[i + 1])
			ft_printf(" ");
		i++;
	}
}

int	built_in_echo(t_command *command)
{
	char	**aux;

	aux = command->argv;
	if (command->argc == 1)
		ft_printf("\n");
	else if (command->argc == 2 && ft_strncmp(command->argv[1], "-n", 3) == 0)
		;
	else if (ft_strncmp(command->argv[1], "-n", 3) != 0)
	{
		printmatrix(aux);
		ft_printf("\n");
	}
	else
		printmatrix_n(aux);
	return (0);
}
