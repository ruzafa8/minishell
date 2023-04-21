#include "minishell.h"

void	loop_shell(t_shell_data *data)
{
	char		*line;
	char		*aux;
	int 		status;
	t_list		*tokens;
	t_list		*commands;

	status = 1;
	while (status)
	{
		ft_printf("> ");
		aux = ft_get_next_line(0);//TODO: cuidao con los leaks
		line = ft_strtrim(aux, "\n");
		free(aux);
		tokens = lexer(line, data);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		commands = parser(tokens);
		lex_free_token_list(&tokens);
		if (!commands)
		{
			free(line);
			continue ;
		}
		status = execute(commands, data);
		pars_free_command_list(&commands);
		free(line);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
