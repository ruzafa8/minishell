#include "minishell.h"

void	append_last_token(t_list **tokens, char **cmd)
{
	t_token	*token;
	char	*substr;
	char	*aux;

	token = ft_lstlast(*tokens)->content;
	substr = ft_substr(*cmd, 0, 1);
	aux = ft_strjoin(token->value, substr);
	free(substr);
	free(token->value);
	token->value = aux;
}
