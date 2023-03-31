/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:49:29 by amorilla          #+#    #+#             */
/*   Updated: 2023/03/31 21:15:10 by amorilla         ###   ########.fr       */
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
	char **args; //argumentos del programa generic
} t_instruction;

t_instruction	*parse(char *str);
int				execute(t_instruction *instr);
void			loop_shell(char **env);

#endif