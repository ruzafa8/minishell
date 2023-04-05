#include "minishell.h"

t_list	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (ft_lstnew(token));
}

static void	free_token(void *token)
{
	if (!token)
		return ;
	free(((t_token *)token)->value);
	free(token);
}

void	free_token_list(t_list **lst)
{
	if (!lst)
		return ;
	ft_lstclear(lst, &free_token);
	ft_printf("free token list\n");
}
