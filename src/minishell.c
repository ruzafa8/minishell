/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:49:26 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 19:54:34 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **args, char **env)
{
	(void)argc;
	(void)args;
	char **path;
	
	path = get_path(env);
	loop_shell(path);
	return (0);
}