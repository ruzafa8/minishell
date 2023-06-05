/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:50:38 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:51:05 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **args, char **env)
{
	t_shell_data	*shell_data;

	(void)argc;
	(void)args;
	shell_data = init_shell_data(env);
	loop_shell(shell_data);
	return (0);
}