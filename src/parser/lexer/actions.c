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

void	append_var_name(t_list **tokens, char **cmd)
{
	t_token	*token;
	char	*substr;
	char	*aux;

	token = ft_lstlast(*tokens)->content;
	substr = ft_substr(*cmd, 0, 1);
	aux = ft_strjoin(token->var_name, substr);
	free(substr);
	free(token->var_name);
	token->var_name = aux;
}

void	substitute_env_var(t_list **tokens, t_shell_data *data)
{
	t_token	*token;
	char	*env_value;
	char	*aux;

	token = ft_lstlast(*tokens)->content;
	if (*(token->var_name) != 0)
	{
		env_value = get_env_value(data, token->var_name);
		if (env_value)
		{
			aux = ft_strjoin(token->value, env_value);
			free(token->value);
			token->value = aux;
			free(env_value);
		}
		free(token->var_name);
		token->var_name = ft_strdup("");
	}
	else
	{
		aux = ft_strjoin(token->value, "$");
		free(token->value);
		token->value = aux;
	}
}
