


#include "minishell.h"


//TODO: NO ES VOID , HAY devolvimientos del arbore
t_list	*parser(t_list *tokens)
{
	t_pars_st	state;

	//tokens nunca puede ser null???? se sale antes
	state = PARS_START;
	while (tokens)
	{
		if (state == PARS_START)
			pars_start_st(tokens, &state);
		else if (state == PARS_COMMAND)
			pars_command_st(tokens, &state);
		else if (state == PARS_REDIR_IN)
			pars_redirin_st(tokens, &state);
		else if (state == PARS_REDIR_OUT)
			pars_redirout_st(tokens, &state);
		else if (state == PARS_REDIR_OUT_APPEND)
			pars_rediroappe_st(tokens, &state);
		else if (state == PARS_REDIR_IN_HEREDOC)
			pars_redheredoc_st(tokens, &state);
		else if (state == PARS_INVALID)
			pars_invalid_st(tokens, &state);
		tokens = tokens->next;
	}
	if (state != PARS_COMMAND)
	{
		//TODO ten cuidao con el free fire 
		//TODO PONERLO EL PRINTF EN EL STERROR
		ft_printf("minishell: syntax error.\n");
		//return (free_tree(), (t_ast *) 0);
	}
	//TODO: pONER BIEN EL NOMBRE DE LA VARIABLE
	return (0);
}

t_pars_st	pars_next_state(t_pars_st state, t_token *token)
{
	if (state == PARS_COMMAND && token->type == TOK_PIPE)
		return (PARS_START);
	else if ((state == PARS_START && token->type == TOK_PIPE)
		|| (state == PARS_REDIR_IN && token->type != TOK_WORD)
		|| (state == PARS_REDIR_IN_HEREDOC && token->type != TOK_WORD)
		|| (state == PARS_REDIR_OUT && token->type != TOK_WORD)
		|| (state == PARS_REDIR_OUT_APPEND && token->type != TOK_WORD))
		return (PARS_INVALID);
	else if ((state == PARS_START && token->type == TOK_WORD)
		|| (state == PARS_REDIR_IN && token->type == TOK_WORD)
		|| (state == PARS_REDIR_IN_HEREDOC && token->type == TOK_WORD)
		|| (state == PARS_REDIR_OUT && token->type == TOK_WORD)
		|| (state == PARS_REDIR_OUT_APPEND && token->type == TOK_WORD))
		return (PARS_COMMAND);
	else if ((state == PARS_START && token->type == TOK_REDIR_IN)
		|| (state == PARS_COMMAND && token->type == TOK_REDIR_IN))
		return (PARS_REDIR_IN);
	else if ((state == PARS_START && token->type == TOK_REDIR_IN_HEREDOC)
		|| (state == PARS_COMMAND && token->type == TOK_REDIR_IN_HEREDOC))
		return (PARS_REDIR_IN_HEREDOC);
	else if ((state == PARS_START && token->type == TOK_REDIR_OUT)
		|| (state == PARS_COMMAND && token->type == TOK_REDIR_OUT))
		return (PARS_REDIR_OUT);
	else if ((state == PARS_START && token->type == TOK_REDIR_OUT_APPEND)
		|| (state == PARS_COMMAND && token->type == TOK_REDIR_OUT_APPEND))
		return (PARS_REDIR_OUT_APPEND);
	return (state);
}
