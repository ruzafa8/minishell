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
			// Iterate commands to print them
			t_list	*tmp = commands;
			while (tmp)
			{
				t_command *command = tmp->content;
				ft_printf("command: %s\n", command->argv[0]);
				int i = 0;
				while (i < command->argc)
				{
					ft_printf("arg: %s\n", command->argv[i]);
					i++;
				}
				tmp = tmp->next;
			}
			status = execute(commands, data);
			free_token_list(&tokens);
		}
		free(line);
		// free(instr);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}
