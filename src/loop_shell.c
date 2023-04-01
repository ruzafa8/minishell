/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:51:09 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 22:14:21 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_shell(char **path, char **env)
{
	char			*line;
	t_instruction	*instr;
	int status;

	status = 1;
	while (status)
	{
		ft_printf("> ");
		line = ft_get_next_line(1);//TODO: cuidao con los leaks
		line = ft_strtrim(line, "\n");
		instr = parse(line);
		status = execute(instr, path, env);
		free(line);
		free(instr);
	}
}