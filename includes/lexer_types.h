/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:13:29 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:12 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TYPES_H
# define LEXER_TYPES_H

typedef enum e_lexer_state
{
	LEX_START,
	LEX_SIMPLE_QUOTE,
	LEX_DOUBLE_QUOTE,
	LEX_WORD,
	LEX_VAR,
	LEX_VAR_DOUBLE_QUOTE
}	t_lex_st;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_OUT_APPEND,
	TOK_HDOC,
	TOK_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	char			*var_name;
	t_token_type	type;
}	t_token;

#endif