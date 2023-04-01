/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:49:29 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 21:43:55 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
# include <unistd.h>
# include <stdio.h>

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
	char *directory;
	char *instruction; //programa generic a ejecutar
	char *args; //argumentos del programa generic
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
int				execute(t_instruction *instr, char **path);
void			loop_shell(char **path);
void			free_path(char **path);
char			**get_path(char **env);
char			*check_access(char *command, char **path);

#endif