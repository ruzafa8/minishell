/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:49:55 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:49:58 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_nextline(void)
{
	char	*aux;
	char	*current_dir;
	char	*prompt;
	char	*line;

	current_dir = getcwd(NULL, 0);
	aux = ft_strjoin("ConchaBB ", current_dir);
	prompt = ft_strjoin(aux, " > ");
	line = readline(prompt);
	return (free(current_dir), free(aux), free(prompt), line);
}

void	loop_shell(t_shell_data *data)
{
	char		*line;
	int 		status;
	t_list		*tokens;

	status = 1;
	data->dup_stdin = dup(STDIN_FILENO);
	data->dup_stdout = dup(STDOUT_FILENO);
	// set señales modo interactivo CONTROL C HACE UN SALTO DE LINEA Y YA Y CTRL \ NO HACE NI MIERDAS
	while (status)
	{
		set_signals_interactive();
		line = get_nextline();
		add_history(line);
		set_signals_noninteractive();
		//SI GETNEXLINE DEVUELVE NULL (CONTROL D) 
		expand_variables(&line, data, 0);
		tokens = lexer(line, data);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		data->commands = parser(tokens, data);
		lex_free_token_list(&tokens);
		if (!data->commands)
		{
			free(line);
			continue ;
		}
		if (ft_lstsize(data->commands) == 1)
			status = execute(data->commands, data);
		else if (ft_lstsize(data->commands) > 1)
			status = execute_pipex(data);
		if (status != 0)
			ft_printf("%s\n", strerror(status));//perror
		pars_free_command_list(&(data->commands));
		free(line);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
