


#include "minishell.h"

void	pars_start_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	//ft_printf("estoy en el estado START\n");
	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		pars_append_new_command(commands, token->value);
}
void	pars_command_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	//ft_printf("estoy en el estado COMMAND\n");
	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		pars_append_arg_to_command(*commands, token->value);
}
void	pars_redirin_st(t_list *tokens, t_pars_st *state)
{
	//ft_printf("estoy en el estado REDIR IN\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redirout_st(t_list *tokens, t_pars_st *state)
{
	//ft_printf("estoy en el estado REDIR OUT\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_rediroappe_st(t_list *tokens, t_pars_st *state)
{
	//ft_printf("estoy en el estado REDIR OUT APPEND\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redheredoc_st(t_list *tokens, t_pars_st *state)
{
	//ft_printf("estoy en el estado REDIR HEREDOC\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_invalid_st(t_list *tokens, t_pars_st *state)
{
	//ft_printf("estoy en el estado BASURA\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}