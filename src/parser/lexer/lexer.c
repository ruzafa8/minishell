/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:28:19 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 19:28:21 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_st	lex_next_state(t_lex_st state, char command)
{
	if ((state == LEX_SIMPLE_QUOTE && command == '\'')
		|| (state == LEX_DOUBLE_QUOTE && command == '"')
		|| (state == LEX_START && !ft_strchr("<' |\">", command)))
		return (LEX_WORD);
	else if ((state == LEX_START && command == '\'')
		|| (state == LEX_WORD && command == '\''))
		return (LEX_SIMPLE_QUOTE);
	else if ((state == LEX_START && command == '"')
		|| (state == LEX_WORD && command == '"'))
		return (LEX_DOUBLE_QUOTE);
	else if ((state == LEX_WORD && ft_strchr("< |>", command)))
		return (LEX_START);
	return (state);
}

t_list	*lexer(char *command, t_shell_data *data)
{
	t_lex_st	state;
	t_list		*tokens;

	(void) data;
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
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		ft_printf("minishell: syntax error: quote not closed.\n");
		return (lex_free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}
