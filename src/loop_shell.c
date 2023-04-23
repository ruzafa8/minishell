#include "minishell.h"

char	*get_nextline()
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
	t_list		*commands;

	status = 1;
	while (status)
	{
		line = get_nextline();
		add_history(line);
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
