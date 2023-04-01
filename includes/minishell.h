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

typedef struct s_instruction
{
	t_type type;
	
	char *directory; //si es cd
	
	char *instruction; //programa generic a ejecutar sin el path metido
	char **args; //argumentos del programa generic y el programa
} t_instruction;

typedef struct u_command
{
	t_type	type;
	t_data	*data;
}	t_command;

typedef union u_data
{
	t_cd		*cd;
	t_generic	*generic;
}	t_data;

typedef struct s_cd
{
	char	*path;
}	t_cd;

typedef struct s_generic
{
	char	*command;
	char	**full_command;
}	t_generic;

t_instruction	*parse(char *str);
int				execute(t_instruction *instr, char **path, char **env);
void			loop_shell(char **path, char **env);
void			free_path(char **path);
char			**get_path(char **env);
char			*check_access(char *command, char **path);

#endif