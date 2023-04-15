#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
# include "lexer_types.h"
# include "parser_types.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef enum e_type
{
	CD,
	GENERIC,
	PWD,
	ENV,
	ECHO,
	EXPORT,
	UNSET,
	EXIT
}	t_type;

typedef struct s_cd
{
	char	*path;
}	t_cd;

typedef struct s_generic
{
	char	*command;
	char	**full_command;
}	t_generic;

typedef union u_data
{
	t_cd		*cd;
	t_generic	*generic;
}	t_data;

typedef struct u_command
{
	t_type	type;
	t_data	*data;
}	t_command;

t_command	*parse(char *str);
int			execute(t_command *instr, char **path, char **env);
void		loop_shell(char **path, char **env);
void		free_path(char **path);
char		**get_path(char **env);
char		*check_access(char *command, char **path);
t_command	*create_cd(char *path);
void		free_cd(t_data	*data);
t_command	*create_generic(char *command, char **full_command);
void		free_command(t_command *command);
int			built_in_cd(t_command *istr, char **env);
char		*get_env_value(char **env, char *key);
t_command	*create_pwd(void);
int			exec_pwd(void);


/**** token functions ******/

t_list		*lexer(char *command_str, char **env);
t_list		*create_token(t_token_type type, char *value);
void		free_token_list(t_list **lst);
void		append_last_token(t_list **tokens, char **cmd);
void		append_var_name(t_list **tokens, char **cmd);
void		substitute_env_var(t_list **tokens, char **env);

void		lex_quote_states(char **cmd, t_lex_st *st, t_list **res, char q);
void		lex_var_state(char **cmd, t_lex_st *st, t_list **res, char **env);
void		lex_var_double_st(char **cmd, t_lex_st *st, t_list **l, char **env);
void		lex_word_state(char **cmd, t_lex_st *st, t_list **res);
void		lex_start_state(char **command, t_lex_st *state, t_list **res);
t_lex_st	lex_next_state(t_lex_st state, char command);

/**** parser functions ******/

void		parser(t_list *tokens);
t_pars_st	pars_next_state(t_pars_st state, t_token *token);
void		pars_start_st(t_list *tokens, t_pars_st *state);
void		pars_command_st(t_list *tokens, t_pars_st *state);
void		pars_redirin_st(t_list *tokens, t_pars_st *state);
void		pars_redirout_st(t_list *tokens, t_pars_st *state);
void		pars_rediroappe_st(t_list *tokens, t_pars_st *state);
void		pars_redheredoc_st(t_list *tokens, t_pars_st *state);
void		pars_invalid_st(t_list *tokens, t_pars_st *state);
#endif