/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:51:09 by amorilla          #+#    #+#             */
/*   Updated: 2023/03/31 21:15:02 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	loop_shell(char **env)
{
	char			*line;
	t_instruction	*instr;
	int status;

	status = 1;
	while (status)
	{
		ft_printf("> ");
		line = ft_get_next_line(1);
		instr = parse(line);
		status = execute(instr);
		free(line);
		free(instr);
	}
}