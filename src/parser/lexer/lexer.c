#include "minishell.h"

static t_lexer_state	next_state(t_lexer_state state, char command)
{
	if ((state == LEX_SIMPLE_QUOTE && command == '\'')
		|| (state == LEX_DOUBLE_QUOTE && command == '"')
		|| (state == LEX_START && !ft_strchr("<' $|\">", command))
		|| (state == LEX_VAR && command == ' ')
		|| (state == LEX_VAR_DOUBLE_QUOTE && command == '"'))
		return (LEX_WORD);
	else if (state == LEX_DOUBLE_QUOTE && command == '$')
		return (LEX_VAR_DOUBLE_QUOTE);
	else if ((state == LEX_START && command == '\'')
		|| (state == LEX_WORD && command == '\'')
		|| (state == LEX_VAR && command == '\''))
		return (LEX_SIMPLE_QUOTE);
	else if ((state == LEX_START && command == '"')
		|| (state == LEX_WORD && command == '"')
		|| (state == LEX_VAR && command == '"')
		|| (state == LEX_VAR_DOUBLE_QUOTE && ft_strchr("<'| >", command)))
		return (LEX_DOUBLE_QUOTE);
	else if ((state == LEX_START && command == '$')
		|| (state == LEX_WORD && command == '$'))
		return (LEX_VAR);
	else if ((state == LEX_WORD && ft_strchr("< |>", command))
		|| (state == LEX_VAR && ft_strchr("<|>", command)))
		return (LEX_START);
	return (state);
}

static void	simple_quote_state(char **cmd, t_lexer_state *st, t_list **res)
{
	*st = next_state(*st, **cmd);
	if (**cmd != '\'')
		append_last_token(res, cmd);
	(*cmd)++;
}

static void	double_quote_state(char **cmd, t_lexer_state *st, t_list **res)
{
	*st = next_state(*st, **cmd);
	if (!ft_strchr("$\"", **cmd))
		append_last_token(res, cmd);
	(*cmd)++;
}

static void var_state(char **cmd, t_lexer_state *st, t_list **res, char **env)
{
	*st = next_state(*st, **cmd);
	if (ft_strchr("<' $|\">", **cmd))
		substitute_env_var(res, env);
	if (**cmd == '|')
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	else if (**cmd == '>' && *((*cmd) + 1) == '>')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
		(*cmd)++;
	}
	else if (**cmd == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	else if (**cmd == '<' && *((*cmd) + 1) == '<')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*cmd)++;
	}
	else if (**cmd == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	else if (**cmd == ' ')
		ft_lstadd_back(res, create_token(TOK_WORD, ft_strdup("")));
	else if (!ft_strchr("'\"$", **cmd))
		append_var_name(res, cmd);
	(*cmd)++;
}

static void var_double_state(char **cmd, t_lexer_state *st, t_list **res, char **env)
{
	*st = next_state(*st, **cmd);
	if (ft_strchr("<' $|\">", **cmd))
		substitute_env_var(res, env);
	if (!ft_strchr("\"$", **cmd))
		append_var_name(res, cmd);
	(*cmd)++;
}

static void	word_state(char **cmd, t_lexer_state *st, t_list **res)
{
	*st = next_state(*st, **cmd);
	if (**cmd == '|')
		ft_lstadd_back(res, create_token(TOK_PIPE, 0));
	else if (**cmd == '>' && *((*cmd) + 1) == '>')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT_APPEND, 0));
		(*cmd)++;
	}
	else if (**cmd == '>')
		ft_lstadd_back(res, create_token(TOK_REDIR_OUT, 0));
	else if (**cmd == '<' && *((*cmd) + 1) == '<')
	{
		ft_lstadd_back(res, create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*cmd)++;
	}
	else if (**cmd == '<')
		ft_lstadd_back(res, create_token(TOK_REDIR_IN, 0));
	else if (!ft_strchr(" '\"$", **cmd))
		append_last_token(res, cmd);
	(*cmd)++;
}

static void	start_state(char **command, t_lexer_state *state, t_list **res)
{
	*state = next_state(*state, **command);
	if (ft_strchr("'\"", **command))
		ft_lstadd_back(res, create_token(TOK_WORD, ft_strdup("")));
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
	else if (**command == ' ') {}
	else if (**command == '$')
		ft_lstadd_back(res, create_token(TOK_WORD, ft_strdup("")));
	else
		ft_lstadd_back(res, create_token(TOK_WORD, ft_substr(*command, 0, 1)));
	if ((**command == '>' && *((*command) + 1) == '>')
		|| (**command == '<' && *((*command) + 1) == '<'))
		(*command)++;
	(*command)++;
}

t_list	*lexer(char *command, char **env)
{
	t_lexer_state	state;
	t_list			*tokens;

	state = LEX_START;
	tokens = 0;
	if (!command)
		return (0);
	while (*command)
	{
		if (state == LEX_START)
			start_state(&command, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			simple_quote_state(&command, &state, &tokens);
		else if (state == LEX_DOUBLE_QUOTE)
			double_quote_state(&command, &state, &tokens);
		else if (state == LEX_WORD)
			word_state(&command, &state, &tokens);
		else if (state == LEX_VAR)
			var_state(&command, &state, &tokens, env);
		else if (state == LEX_VAR_DOUBLE_QUOTE)
			var_double_state(&command, &state, &tokens, env);
	}
	if (state == LEX_SIMPLE_QUOTE
		|| state == LEX_DOUBLE_QUOTE
		|| state == LEX_VAR_DOUBLE_QUOTE)
	{
		ft_printf("minishell: syntax error: quote not closed.\n");
		return (free_token_list(&tokens), (t_list *) 0);
	}
	if (state == LEX_VAR)
		substitute_env_var(&tokens, env);
	return (tokens);
}
