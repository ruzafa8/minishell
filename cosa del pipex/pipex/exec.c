/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:25:57 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 21:20:09 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_command(int fd_in, int fd_out, char *command, t_data *data)
{
	int	res;

	px_setstd(fd_in, fd_out);
	close(data->pipe[0]);
	close(data->pipe[1]);
	res = px_exec(ft_split(command, ' '), data->path, data->env);
	perror(strerror(res));
	close(fd_in);
	exit(res);
}

static void	second_command(int fd_in, int fd_out, char *command, t_data *data)
{
	int	res;

	px_setstd(fd_in, fd_out);
	close(data->pipe[1]);
	res = px_exec(ft_split(command, ' '), data->path, data->env);
	perror(strerror(res));
	exit(res);
}

void	px_pipex(char *command1, char *command2, t_data *data)
{
	int		pid1;
	int		pid2;
	int		result_code;

	pipe(data->pipe);
	pid1 = fork();
	if (pid1 < 0)
		exit(pid1);
	if (pid1 == 0)
		first_command(data->in, data->pipe[1], command1, data);
	pid2 = fork();
	if (pid2 < 0)
		exit(pid2);
	if (pid2 == 0)
		second_command(data->pipe[0], data->out, command2, data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	waitpid(pid1, 0, 0);
	waitpid(pid2, &result_code, 0);
	if (WIFEXITED(result_code))
		exit(WEXITSTATUS(result_code));
}

int	px_exec(char **command, char **path, char **env)
{
	char	*full_command;

	full_command = px_check_access(command[0], path);
	if (full_command != 0)
	{
		execve(full_command, command, env);
		return (errno);
	}
	return (127);
}
