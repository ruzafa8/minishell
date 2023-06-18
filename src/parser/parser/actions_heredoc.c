/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 19:34:04 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/06/18 15:53:39 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(int fd, char *value, t_shell_data *data)
{
	char	*line;

	while (1)
	{
		line = readline(" >> ");
		if (!line)
			break ;
		expand_variables(&line, data, 1);
		if (ft_strncmp(line, value, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

t_pars_err	pars_create_heredoc(t_list	*cmds, char *value, t_shell_data *data)
{
	t_command		*command;
	static size_t	next_heredoc_code = 0;
	char			*filename;
	char			*tmp;

	command = (t_command *) ft_lstlast(cmds)->content;
	tmp = ft_itoa(next_heredoc_code++);
	if (!tmp)
		return (PARS_MALLOC_ERROR);
	filename = ft_strjoin("/tmp/.minishel_heredoc_", tmp);
	free(tmp);
	if (!filename)
		return (PARS_MALLOC_ERROR);
	read_heredoc(open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666),
		value, data);
	command->fd_in = open(filename, O_RDONLY, 0666);
	free(filename);
	return (PARS_NO_ERROR);
}
