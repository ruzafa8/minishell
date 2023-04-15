#include "minishell.h"

void	loop_shell(char **path, char **env)
{
	char		*line;
	char		*aux;
	int 		status;
	t_list		*tokens;
	t_list		*commands;

	status = 1;
	(void)env;
	(void)path;
	while (status)
	{
		ft_printf("> ");
		aux = ft_get_next_line(0);//TODO: cuidao con los leaks
		line = ft_strtrim(aux, "\n");
		free(aux);
		tokens = lexer(line, env);
		t_list	*tmp = tokens;
		while (tmp)
		{
			t_token *token = tmp->content;
			if (token->type == TOK_WORD)
				ft_printf("str: %s\n", token->value);
			else if (token->type == TOK_PIPE)
				ft_printf("pipe\n");
			else if (token->type == TOK_REDIR_OUT)
				ft_printf("redir out\n");
			else if (token->type == TOK_REDIR_OUT_APPEND)
				ft_printf("redir out append\n");
			else if (token->type == TOK_REDIR_IN)
				ft_printf("redir in\n");
			else if (token->type == TOK_REDIR_IN_HEREDOC)
				ft_printf("redir in heredoc\n");
			tmp = tmp->next;
		}
		if (tokens)
		{
			commands = parser(tokens);
			status = execute(commands, path, env);
			free_token_list(&tokens);
		}
		free(line);
		// free(instr);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
