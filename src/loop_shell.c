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

	status = 1;
	// set señales modo interactivo CONTROL C HACE UN SALTO DE LINEA Y YA Y CTRL \ NO HACE NI MIERDAS
	while (status)
	{
		line = get_nextline();
		add_history(line);
		//SI GETNEXLINE DEVUELVE NULL (CONTROL D) 
		tokens = lexer(line, data);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		data->commands = parser(tokens);
		lex_free_token_list(&tokens);
		if (!data->commands)
		{
			free(line);
			continue ;
		}
		status = execute_pintapipex(data);
		ft_printf("statusssss: %d\n", status);
		if (status != 0)
			ft_printf("%s\n", strerror(status));//perror
		pars_free_command_list(&(data->commands));
		free(line);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
