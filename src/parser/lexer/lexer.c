#include "minishell.h"

t_list	*lexer(char *command_str)
{
	t_list		*res;

	res = 0;
	while (ft_strncmp(command_str, "", 1) != 0)
	{
		if (ft_strncmp(command_str, " ", 1) == 0)
		{
			command_str++;
			continue ;
		}
		if (ft_strncmp(command_str, "\"", 1) == 0)
		{
			t_token *token = ft_calloc(1, sizeof(t_token));
			token->type = TOK_STR;
			token->value = get_until(command_str + 1, '"');
			ft_lstadd_back(&res, ft_lstnew(token));
			command_str = command_str + ft_strlen(token->value) + 2;
			continue ;
		}
		if (ft_strncmp(command_str, "'", 1) == 0)
		{
			t_token *token = ft_calloc(1, sizeof(t_token));
			token->type = TOK_STR;
			token->value = get_until(command_str + 1, '\'');
			ft_lstadd_back(&res, ft_lstnew(token));
			command_str = command_str + ft_strlen(token->value) + 2;
			continue ;
		}
		if (is_command(command_str, "cd"))
		{
			t_token *token = ft_calloc(1, sizeof(t_token));
			token->type = TOK_CD;
			ft_lstadd_back(&res, ft_lstnew(token));
			command_str = command_str + 2;
			continue ;
		}
		t_token *token = ft_calloc(1, sizeof(t_token));
		token->type = TOK_STR;
		token->value = get_until(command_str, ' ');
		ft_lstadd_back(&res, ft_lstnew(token));
		command_str = command_str + ft_strlen(token->value);
	}
	return (res);
}
