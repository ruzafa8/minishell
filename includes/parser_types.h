#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

typedef enum e_parser_state
{
	PARS_START,
	PARS_COMMAND,
	PARS_REDIR_IN,
	PARS_REDIR_OUT,
	PARS_REDIR_OUT_APPEND,
	PARS_REDIR_IN_HEREDOC,
	PARS_INVALID
}	t_pars_st;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_OUT_APPEND,
	TOK_REDIR_IN_HEREDOC,
	TOK_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	char			*var_name;
	t_token_type	type;
}	t_token;

#endif