/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:56:11 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 19:56:38 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars_err	pars_redheredoc_st(
	t_list *tokens,
	t_pars_st *state,
	t_list **cmds,
	t_shell_data *data
) {
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token->type == TOK_WORD)
		return (pars_create_heredoc(*cmds, token->value, data));
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_invalid_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
	return (PARS_SYNTAX_ERROR);
}
