/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:28:31 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/04 19:28:31 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lex_create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	token->var_name = ft_strdup("");
	return (ft_lstnew(token));
}

static void	free_token(void *token)
{
	t_token	*t;

	t = (t_token *) token;
	if (!token)
		return ;
	if (t->value)
		free(t->value);
	if (t->var_name)
		free(t->var_name);
	free(t);
}

void	lex_free_token_list(t_list **lst)
{
	if (!lst)
		return ;
	ft_lstclear(lst, &free_token);
}
