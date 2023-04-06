#include "minishell.h"

static t_lexer_state	next_state(t_lexer_state current_state, char command)
{
	if (current_state == LEX_SIMPLE_QUOTE && command == '\'')
		return (LEX_WORD);
	else if (current_state == LEX_DOUBLE_QUOTE && command == '"')
		return (LEX_WORD);
	else if (current_state == LEX_START && command == '\'')
		return (LEX_SIMPLE_QUOTE);
	else if (current_state == LEX_START && command == '"')
		return (LEX_DOUBLE_QUOTE);
	else if (current_state == LEX_START && !ft_strchr("< |>", command))
		return (LEX_WORD);
	else if (current_state == LEX_WORD && command == '\'')
		return (LEX_SIMPLE_QUOTE);
	else if (current_state == LEX_WORD && command == '"')
		return (LEX_DOUBLE_QUOTE);
	else if (current_state == LEX_WORD && ft_strchr("< |>", command))
		return (LEX_START);
	return (current_state);
}

static void	quote_state(char **cmd, t_lexer_state *st, t_list **res, char q)
{
	*st = next_state(*st, **cmd);
	if (**cmd != q)
		append_last_token(res, cmd);
	(*cmd)++;
}

static void	word_state(char **cmd, t_lexer_state *st, t_list **res)
{
	*st = next_state(*st, **cmd);
	if (**cmd == '|')
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	else if (**cmd == '>' && **(cmd + 1) == '>')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
		(*cmd)++;
	}
	else if (**cmd == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	else if (**cmd == '<' && **(cmd + 1) == '<')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*cmd)++;
	}
	else if (**cmd == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	else if (!ft_strchr(" '\"", **cmd))
		append_last_token(res, cmd);
	(*cmd)++;
}

static void	start_state(char **command, t_lexer_state *state, t_list **res)
{
	*state = next_state(*state, **command);
	if (ft_strchr("'\"", **command))
		ft_lstadd_back(res, create_token(TOK_WORD,
				(char *) ft_calloc(0, sizeof(char))));
	else if (**command == '|')
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	else if (**command == '>' && *((*command) + 1) == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
	else if (**command == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	else if (**command == '<' && *((*command) + 1) == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
	else if (**command == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	else if (**command != ' ')
		ft_lstadd_back(res, create_token(TOK_WORD, ft_substr(*command, 0, 1)));
	if ((**command == '>' && *((*command) + 1) == '>')
		|| (**command == '<' && *((*command)) == '<'))
		(*command)++;
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
			start_state(&command, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			quote_state(&command, &state, &tokens, '\'');
		else if (state == LEX_DOUBLE_QUOTE)
			quote_state(&command, &state, &tokens, '"');
		else if (state == LEX_WORD)
			word_state(&command, &state, &tokens);
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		ft_printf("minishell: syntax error: quote not closed.\n");
		return (free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}
