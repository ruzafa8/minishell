/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:42 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 21:26:44 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execute_generic(t_instruction *instr)
{
	int		pid1;
	int		result_code;

	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
		
	waitpid(pid1, 0, 0);
	if (WIFEXITED(result_code))
		exit(WEXITSTATUS(result_code));
}


int	execute(t_instruction *instr, char **path)
{
	int	status;

	status = 1;
	if (instr->type == CD)
		status = chdir(instr->directory);
	else if (instr->type == GENERIC)
		status = execute_generic(instr);
	return (status);
}

