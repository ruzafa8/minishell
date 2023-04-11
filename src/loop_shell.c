#include "minishell.h"

void	loop_shell(char **path, char **env)
{
	char		*line;
	char		*aux;
	t_command	*instr;
	int 		status;

	status = 1;
	(void)env;
	(void)path;
	(void)instr;
	while (status)
	{
		ft_printf("> ");
		aux = ft_get_next_line(0);//TODO: cuidao con los leaks
		line = ft_strtrim(aux, "\n");
		free(aux);
		t_list	*res = lexer(line, env);
		t_list	*tmp = res;
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
		free_token_list(&res);
		// instr = parse(line);
		// status = execute(instr, path, env);
		free(line);
		// free(instr);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
