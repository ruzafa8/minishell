/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:53 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/03/11 21:17:05 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		permission;
	t_data	data;

	if (argc != 5)
		return (103);
	data.env = env;
	data.path = px_get_path(env);
	data.in = open(argv[1], O_RDONLY);
	if (data.in < 0)
		return (errno);
	permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	data.out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, permission);
	if (data.out < 0)
		return (errno);
	px_pipex(argv[2], argv[3], &data);
	px_free_path(data.path);
	return (errno);
}
