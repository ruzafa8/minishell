/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:30:41 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 21:23:10 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft/ft.h"

typedef struct s_data
{
	int		*pipe;
	int		in;
	int		out;
	char	*command;
	char	**path;
	char	**env;
}			t_data;

char	**px_get_path(char **env);
void	px_free_path(char **path);

char	*px_check_access(char *command, char **path);

int		px_exec(char **command, char **path, char **env);
void	px_pipex(char *command1, char *command2, t_data *data);

/* utils file */
void	px_setstd(int fd_in, int fd_out);

#endif
