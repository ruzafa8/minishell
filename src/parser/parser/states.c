


#include "minishell.h"

void	pars_start_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado START\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_command_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado COMMAND\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redirin_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado REDIR IN\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redirout_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado REDIR OUT\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_rediroappe_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado REDIR OUT APPEND\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_redheredoc_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado REDIR HEREDOC\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}
void	pars_invalid_st(t_list *tokens, t_pars_st *state)
{
	ft_printf("estoy en el estado BASURA\n");
	*state = pars_next_state(*state, (t_token *) tokens->content);
}