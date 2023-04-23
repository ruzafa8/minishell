


#include "minishell.h"

void	pars_start_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		pars_append_new_command(commands, token->value);
	if (token->type == TOK_REDIR_IN)
		pars_append_new_command(commands, 0);
	if (token->type == TOK_REDIR_OUT)
		pars_append_new_command(commands, 0);
	if (token->type == TOK_REDIR_OUT_APPEND)
		pars_append_new_command(commands, 0);
	if (token->type == TOK_REDIR_IN_HEREDOC)
		pars_append_new_command(commands, 0);
}
void	pars_command_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		pars_append_arg_to_command(*commands, token->value);
}
void	pars_redirin_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redirout_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_rediroappe_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redheredoc_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_invalid_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
}