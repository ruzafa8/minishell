#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
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

typedef struct s_shell_data
{
	bool		interactive;
	//t_token		*token;
	//char		*user_input;
	char		**env;
	char		*working_dir;
	char		*old_working_dir;
	//t_command	*cmd;
	//pid_t		pid;
}	t_shell_data;


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


#endif