#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
# include "lexer_types.h"
# include "parser_types.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_command
{
	char	**argv;
	int		argc;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_shell_data
{
	//int		interactive;
	//t_token		*token;
	//char		*user_input;
	char		**env;
	//char		*working_dir;
	//char		*old_working_dir;
	//t_command	*cmd;
	//pid_t		pid;
}	t_shell_data;

int			execute(t_list *instr, t_shell_data *data);
void		loop_shell(t_shell_data *data);
void		free_path(char **path);
char		**get_path(char **env);
char		*check_access(char *command, char **path);
char		*get_env_value(t_shell_data *data, char *key);
int				exec_pwd(void);

/**** env functions ******/

int				env_size(char **env);
int				init_env(t_shell_data *aux, char **env);
t_shell_data	*init_shell_data(char **env);
void			free_ptr(void *ptr);
int				get_env_var_index(char **env, char *var);
int				set_env_var(t_shell_data *data, char *key, char *value);
int				remove_env_var(t_shell_data *data, int idx);

/**** token functions ******/

t_list		*lexer(char *command_str, t_shell_data *data);
t_list		*lex_create_token(t_token_type type, char *value);
void		lex_free_token_list(t_list **lst);
void		append_last_token(t_list **tokens, char **cmd);
void		append_var_name(t_list **tokens, char **cmd);
void		substitute_env_var(t_list **tokens, t_shell_data *data);

void		lex_quote_states(char **cmd, t_lex_st *st, t_list **res, char q);
void		lex_var_state(char **cmd, t_lex_st *st, t_list **res, t_shell_data *data);
void		lex_var_double_st(char **cmd, t_lex_st *st, t_list **l, t_shell_data *d);
void		lex_word_state(char **cmd, t_lex_st *st, t_list **res);
void		lex_start_state(char **command, t_lex_st *state, t_list **res);
t_lex_st	lex_next_state(t_lex_st state, char command);

/**** parser functions ******/

t_list			*parser(t_list *tokens);
t_pars_st		pars_next_state(t_pars_st state, t_token *token);
t_pars_err		pars_start_st(t_list *tokens, t_pars_st *state, t_list **commands);
t_pars_err		pars_command_st(t_list *tokens, t_pars_st *state, t_list **commands);
t_pars_err		pars_redirin_st(t_list *tokens, t_pars_st *state, t_list **commands);
t_pars_err		pars_redirout_st(t_list *tokens, t_pars_st *state, t_list **commands);
t_pars_err		pars_rediroappe_st(t_list *tokens, t_pars_st *state);
t_pars_err		pars_redheredoc_st(t_list *tokens, t_pars_st *state);
t_pars_err		pars_invalid_st(t_list *tokens, t_pars_st *state);

t_pars_err		pars_append_arg_to_command(t_list *commands, char *value);
t_pars_err		pars_append_new_command(t_list **commands, char *value);
void			pars_free_command_list(t_list **cmds);
t_pars_err		pars_set_stdin(t_list *commands, char *filename);
t_pars_err		pars_set_stdout(t_list *commands, char *filename);


/**** builtin functions ******/

int	built_in_env(t_command *command, t_shell_data *data);
int	built_in_cd(t_command *instr, t_shell_data *data);


#endif