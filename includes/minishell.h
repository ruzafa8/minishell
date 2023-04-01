/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:49:29 by amorilla          #+#    #+#             */
/*   Updated: 2023/04/01 20:39:53 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/ft.h"
# include <unistd.h>
# include <stdio.h>

typedef enum e_type
{
	CD, GENERIC, PWD, ENV, ECHO, EXPORT, UNSET, EXIT
} t_type;

typedef struct s_instruction
{
	t_type type;
	char *directory;
	char *instruction; //programa generic a ejecutar
	char *args; //argumentos del programa generic
} t_instruction;

t_instruction	*parse(char *str);
int				execute(t_instruction *instr, char **path, char **env);
void			loop_shell(char **path, char **env);
void			free_path(char **path);
char			**get_path(char **env);
char			*check_access(char *command, char **path);

#endif