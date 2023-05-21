


#include "minishell.h"

void	print_error(t_pars_st state, t_pars_err err)
{
	if (state != PARS_COMMAND || err == PARS_SYNTAX_ERROR)
		ft_printf("minishell: syntax error.\n");
	else if (err == PARS_MALLOC_ERROR)
		ft_printf("minishell: memory error\n");
	else if (err == PARS_NO_SUCH_FILE_OR_DIR)
		ft_printf("minishell: no such file or directory\n");
}

static void	set_pipes(t_list *instr)
{
	t_command	*cmd;
	t_command	*next;
	int			pipes[2];

	while (instr)
	{
		cmd = (t_command *) instr->content;
		if (instr->next)
		{
			next = (t_command *) instr->next->content;
			pipe(pipes);
			if (cmd->fd_out == 0)
				ft_memcpy(&(cmd->fd_out), pipes + 1, sizeof(int));
			else
				close(pipes[1]);
			if (next->fd_in == 0)
				ft_memcpy(&(next->fd_in), pipes + 0, sizeof(int));
			else
				close(pipes[0]);
		}
		instr = instr->next;
	}
}

t_list	*parser(t_list *tokens)
{
	t_pars_st	state;
	t_list		*commands;
	t_pars_err	err;

	commands = 0;
	state = PARS_START;
	err = PARS_NO_ERROR;
	while (tokens && err == PARS_NO_ERROR)
	{
		if (state == PARS_START)
			err = pars_start_st(tokens, &state, &commands);
		else if (state == PARS_COMMAND)
			err = pars_command_st(tokens, &state, &commands);
		else if (state == PARS_REDIR_IN)
			err = pars_redirin_st(tokens, &state, &commands);
		else if (state == PARS_REDIR_OUT)
			err = pars_redirout_st(tokens, &state, &commands);
		else if (state == PARS_REDIR_OUT_APPEND)
			err = pars_rediroappe_st(tokens, &state, &commands);
		else if (state == PARS_REDIR_IN_HEREDOC)
			err = pars_redheredoc_st(tokens, &state);
		else if (state == PARS_INVALID)
			err = pars_invalid_st(tokens, &state);
		tokens = tokens->next;
	}
	print_error(state, err);
	if (err != PARS_NO_ERROR || state == PARS_INVALID)
		return (pars_free_command_list(&commands), (t_list *) 0);
	set_pipes(commands);
	return (commands);
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
