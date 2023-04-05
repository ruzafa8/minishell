#include "minishell.h"

void	process_quote_state(char **cmd, t_lexer_state *st, t_list **res, char q)
{
	t_token	*token;

	if (**cmd == q)
		*st = LEX_WORD;
	else
	{
		token = ft_lstlast(*res)->content;
		token->value = ft_strjoin(token->value, ft_substr(*cmd, 0, 1)); //TODO: Leaks?
	}
	(*cmd)++;
}

void	process_word_state(char **cmd, t_lexer_state *st, t_list **res)
{
	t_token	*token;
	char	*aux;
	char	*substr;

	if (**cmd == '\'')
		*st = LEX_SIMPLE_QUOTE;
	else if (**cmd == '"')
		*st = LEX_DOUBLE_QUOTE;
	else if (**cmd == ' ')
		*st = LEX_START;
	else if (**cmd == '|')
	{
		*st = LEX_START;
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	}
	else if (**cmd == '>' && **(cmd + 1) == '>')
	{
		*st = LEX_START;
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
		(*cmd)++;
	}
	else if (**cmd == '>')
	{
		*st = LEX_START;
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	}
	else if (**cmd == '<' && **(cmd + 1) == '<')
	{
		*st = LEX_START;
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*cmd)++;
	}
	else if (**cmd == '<')
	{
		*st = LEX_START;
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	}
	else
	{
		token = ft_lstlast(*res)->content;
		substr = ft_substr(*cmd, 0, 1);
		aux = ft_strjoin(token->value, substr);
		free(substr);
		free(token->value);
		token->value = aux;
	}
	(*cmd)++;
}

void	process_start_state(char **command, t_lexer_state *state, t_list **res)
{
	if (**command == '\'')
	{
		ft_lstadd_back(res, create_token(TOK_WORD, (char *) ft_calloc(0, sizeof(char))));
		*state = LEX_SIMPLE_QUOTE;
	}
	else if (**command == '"')
	{
		ft_lstadd_back(res, create_token(TOK_WORD, (char *) ft_calloc(0, sizeof(char))));
		*state = LEX_DOUBLE_QUOTE;
	}
	else if (**command == ' ') {}
		// do nothing
	else if (**command == '|')
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	else if (**command == '>' && command + 1 && **(command + 1) == '>')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
		(*command)++;
	}
	else if (**command == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	else if (**command == '<' && command + 1 && **(command + 1) == '<')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*command)++;
	}
	else if (**command == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	else
	{
		*state = LEX_WORD;
		ft_lstadd_back(res, create_token(TOK_WORD, ft_substr(*command, 0, 1)));
	}
	(*command)++;
}

t_list	*lexer(char *command)
{
	t_lexer_state	state;
	t_list			*tokens;

	state = LEX_START;
	tokens = 0;
	while (*command)
	{
		if (state == LEX_START)
			process_start_state(&command, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			process_quote_state(&command, &state, &tokens, '\'');
		else if (state == LEX_DOUBLE_QUOTE)
			process_quote_state(&command, &state, &tokens, '"');
		else if (state == LEX_WORD)
			process_word_state(&command, &state, &tokens);
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		ft_printf("minishell: syntax error: quote not closed.\n");
		return (free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}
