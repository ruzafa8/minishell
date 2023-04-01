/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:10:42 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 20:51:26 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	execaux(char *comand, char **path, char ** env)
{
	
}

static int	execute_generic(t_instruction *instr, char **path, char **env)
{
	int		pid1;
	int		result_code;

	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
	{
		result_code = execaux(instr->instruction, path, env);
		perror(strerror(result_code));
	}
	waitpid(pid1, 0, 0);
	if (WIFEXITED(result_code))
		exit(WEXITSTATUS(result_code));
}


int	execute(t_instruction *instr, char **path, char **env)
{
	int	status;

	status = 127;
	if (instr->type == CD)
		status = chdir(instr->directory);
	else if (instr->type == GENERIC)
		status = execute_generic(instr, path, env);
	return (status);
}

