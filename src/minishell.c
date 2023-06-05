/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:50:38 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:27:57 by aruzafa-         ###   ########.fr       */
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
