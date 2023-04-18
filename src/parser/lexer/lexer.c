#include "minishell.h"

t_lex_st	lex_next_state(t_lex_st state, char command)
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

t_list	*lexer(char *command, t_shell_data *data)
{
	t_lex_st	state;
	t_list		*tokens;

	state = LEX_START;
	tokens = 0;
	if (!command)
		return (0);
	while (*command)
	{
		if (state == LEX_START)
			lex_start_state(&command, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			lex_quote_states(&command, &state, &tokens, '\'');
		else if (state == LEX_DOUBLE_QUOTE)
			lex_quote_states(&command, &state, &tokens, '"');
		else if (state == LEX_WORD)
			lex_word_state(&command, &state, &tokens);
		else if (state == LEX_VAR)
			lex_var_state(&command, &state, &tokens, data);
		else if (state == LEX_VAR_DOUBLE_QUOTE)
			lex_var_double_st(&command, &state, &tokens, data);
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE
		|| state == LEX_VAR_DOUBLE_QUOTE)
	{
		ft_printf("minishell: syntax error: quote not closed.\n");
		return (lex_free_token_list(&tokens), (t_list *) 0);
	}
	if (state == LEX_VAR)
		substitute_env_var(&tokens, data);
	return (tokens);
}
