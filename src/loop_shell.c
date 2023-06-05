/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:49:55 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 17:26:30 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_nextline(void)
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

static t_list	*analyze_line(char **line, t_shell_data *data)
{
	t_list	*tokens;
	t_list	*commands;

	expand_variables(line, data, 0);
	tokens = lexer(*line, data);
	if (!tokens)
		return (0);
	commands = parser(tokens, data);
	lex_free_token_list(&tokens);
	return (commands);
}

/**
 * TODO: status = 1 siempre! 
 * Quitar pa poner shell interactiva o no interactiva (con el flag -c).
 * 
 * TODO: Si es status es error (DIFERENTE DE 0) se hace un strerror(status)
 * pa que salga el error por pantalla, ¿se puede hacer con perror?
 */
void	loop_shell(t_shell_data *data)
{
	char	*line;
	int		status;

	status = 1;
	data->dup_stdin = dup(STDIN_FILENO);
	data->dup_stdout = dup(STDOUT_FILENO);
	while (status)
	{
		set_signals_interactive();
		line = get_nextline();
		add_history(line);
		set_signals_noninteractive();
		data->commands = analyze_line(&line, data);
		free(line);
		if (!data->commands)
			continue ;
		if (ft_lstsize(data->commands) == 1)
			status = execute(data->commands, data);
		else if (ft_lstsize(data->commands) > 1)
			status = execute_pipex(data);
		if (status != 0)
			ft_printf("%s\n", strerror(status));
		pars_free_command_list(&(data->commands));
		status = 1;
	}
}
