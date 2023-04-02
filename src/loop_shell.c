#include "minishell.h"

void	loop_shell(char **path, char **env)
{
	char			*line;
	t_command	*instr;
	int status;

	status = 1;
	(void)env;
	(void)path;
	(void)instr;
	while (status)
	{
		ft_printf("> ");
		line = ft_get_next_line(0);//TODO: cuidao con los leaks
		line = ft_strtrim(line, "\n");
		t_list	*res = lexer(line);
		while (res)
		{
			t_token *token = res->content;
			if (token->type == TOK_STR)
				ft_printf("str: %s\n", token->value);
			else if (token->type == TOK_CD)
				ft_printf("cd\n");
			res = res->next;
		}
		// instr = parse(line);
		// status = execute(instr, path, env);
		// free(line);
		// free(instr);
		status = 1;//quitar pa poner shell interactiva o no interactiva (con el flag -c)
	}
}