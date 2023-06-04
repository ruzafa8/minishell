/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:28:24 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 19:29:19 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_quote_states(char **cmd, t_lex_st *st, t_list **res, char quote)
{
	*st = lex_next_state(*st, **cmd);
	if (quote == '"')
	{
		if (!ft_strchr("\"", **cmd))
			append_last_token(res, cmd);
	}
	else
	{
		if (**cmd != '\'')
			append_last_token(res, cmd);
	}
	(*cmd)++;
}

void	lex_word_state(char **cmd, t_lex_st *st, t_list **res)
{
	*st = lex_next_state(*st, **cmd);
	if (**cmd == '|')
		ft_lstadd_back(res, lex_create_token(TOK_PIPE, 0));
	else if (**cmd == '>' && *((*cmd) + 1) == '>')
	{
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT_APPEND, 0));
		(*cmd)++;
	}
	else if (**cmd == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT, 0));
	else if (**cmd == '<' && *((*cmd) + 1) == '<')
	{
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN_HEREDOC, 0));
		(*cmd)++;
	}
	else if (**cmd == '<')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN, 0));
	else if (!ft_strchr(" '\"", **cmd))
		append_last_token(res, cmd);
	(*cmd)++;
}

void	lex_start_state(char **command, t_lex_st *state, t_list **res)
{
	*state = lex_next_state(*state, **command);
	if (ft_strchr("'\"", **command))
		ft_lstadd_back(res, lex_create_token(TOK_WORD, ft_strdup("")));
	else if (**command == '|')
		ft_lstadd_back(res, lex_create_token(TOK_PIPE, 0));
	else if (**command == '>' && *((*command) + 1) == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT_APPEND, 0));
	else if (**command == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT, 0));
	else if (**command == '<' && *((*command) + 1) == '<')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN_HEREDOC, 0));
	else if (**command == '<')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN, 0));
	else if (**command == ' ')
		;
	else
		ft_lstadd_back(res, lex_create_token(TOK_WORD,
				ft_substr(*command, 0, 1)));
	if ((**command == '>' && *((*command) + 1) == '>')
		|| (**command == '<' && *((*command) + 1) == '<'))
		(*command)++;
	(*command)++;
}
