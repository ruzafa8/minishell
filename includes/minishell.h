/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:13:47 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/08 18:15:02 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
# include "lexer_types.h"
# include "parser_types.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_command
{
	char	**argv;
	int		argc;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_shell_data
{
	char		**env;
	int			dup_stdin;
	int			dup_stdout;
	t_list		*commands;
	char		**exportenv;
	int			last_status;
}	t_shell_data;

typedef struct s_global_sig
{
	int		exit_status;
	pid_t	pid;
}	t_global_sig;

int				execute(t_list *instr, t_shell_data *data);
int				execute_pipex(t_shell_data *data);

void			loop_shell(t_shell_data *data);
void			free_path(char **path);
char			**get_path(char **env);
char			*check_access(char *command, char **path);
char			*get_env_value(t_shell_data *data, char *key);
int				is_builtin(char *command);
int				execute_builtins(t_command *command, t_shell_data *data);

/**** env functions ******/

int				env_size(char **env);
int				init_env(t_shell_data *aux, char **env);
int				init_export_env(t_shell_data *aux, char **env);
t_shell_data	*init_shell_data(char **env);
int				get_env_var_index(char **env, char *var);
int				set_env_var(t_shell_data *data, char *key, char *value);
int				remove_env_var(t_shell_data *data, int idx);
int				remove_exportenv_var(t_shell_data *data, int idx);

/**** token functions ******/

t_list			*lexer(char *command_str, t_shell_data *data);
t_list			*lex_create_token(t_token_type type, char *value);
void			lex_free_token_list(t_list **lst);
void			append_last_token(t_list **tokens, char **cmd);
void			append_var_name(t_list **tokens, char **cmd);
void			substitute_env_var(t_list **tokens, t_shell_data *data);

void			lex_quote_states(char **cmd, t_lex_st *st,
					t_list **res, char q);

void			lex_var_state(char **cmd, t_lex_st *st,
					t_list **res, t_shell_data *data);

void			lex_var_double_st(char **cmd, t_lex_st *st,
					t_list **l, t_shell_data *d);

void			lex_word_state(char **cmd, t_lex_st *st, t_list **res);
void			lex_start_state(char **command, t_lex_st *state, t_list **res);
t_lex_st		lex_next_state(t_lex_st state, char command);

/**** parser functions ******/

t_list			*parser(t_list *tokens, t_shell_data *data);
t_pars_st		pars_next_state(t_pars_st state, t_token *token);
t_pars_err		pars_start_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_command_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_redirin_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_redirout_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_rediroappe_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_redheredoc_st(t_list *tokens, t_pars_st *state,
					t_list **commands, t_shell_data *data);
t_pars_err		pars_invalid_st(t_list *tokens, t_pars_st *state);
t_pars_err		pars_append_arg_to_command(t_list *commands, char *value);
t_pars_err		pars_append_new_command(t_list **commands, char *value);
void			pars_free_command_list(t_list **cmds);
t_pars_err		pars_set_stdin(t_list *commands, char *filename);
t_pars_err		pars_set_stdout(t_list *commands, char *filename, int append);
t_pars_err		pars_create_heredoc(t_list	*commands, char *value,
					t_shell_data *data);

/**** pipes utils ******/

/**
 * Closes all pipes except the ones that are needed for the current
 * instruction.
 */
void			close_pipes(t_shell_data *data, t_list *instr);

/**
 * Function that expands the variables in the given line.
 * @param line the line to expand. It is reallocated to substitute the
 *			   variables.
 * @param data the shell data (To get the env variables)
 * @param expand_quotes if 1, the variables inside simple quotes 
 * 						are expanded. If 0, they are not.
 */
void			expand_variables(char **line, t_shell_data *data,
					int expand_quotes);

/***************************** builtin functions ******************************/

int				built_in_env(t_command *command, t_shell_data *data);
int				built_in_cd(t_command *instr, t_shell_data *data);
int				built_in_export(t_command *command, t_shell_data *data);

/**
 *	Añade la variable al enviroment.
 *	Si ya existe, le cambia el valor, si no, creará una nueva.
 * 
 * @param data: estructura de datos.
 * @param key: clave de la variable.
 * @param value: valor de la variable.
 * 
 * @returns 1 si ha ocurrido, 0 si se ha destruido.
 */
int				set_export_env_var(t_shell_data *data, char *key, char *value);
int				built_in_unset(t_command *command, t_shell_data *data);
int				exec_pwd(void);
int				built_in_echo(t_command *command);
int				built_in_exit(t_command *command, t_shell_data *data);
int				decode_error(int err);

/**** signals functions ******/

void			signal_reset_prompt(int signo);
void			set_signals_interactive(void);
void			signal_print_newline(int signal);
void			set_signals_noninteractive(void);
void			ignore_sigquit(void);
void			sig_init(void);

/****** UTILS *****/
int				print_error(char *cmd, char *detail, char *err_msg, int err);
void			free_envs(t_shell_data *data);
void			del_t_command(void *command);
void			free_ptr(void *ptr);
void			exitshell(t_shell_data *data, int exitcode);

extern t_global_sig	g_sig;

#endif