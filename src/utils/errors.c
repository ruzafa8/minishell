/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:45:23 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/08 18:13:26 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Joins two strings ,the first is a string and the second a literal,
*	freeing the first string.
*	Returns the new concatenated string,
*	or NULL if an error occured.
*/
char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

/*
*	Checks if we have to add quotes around the error detail:
*	"unset: `@': not a valid identifier"
*	Returns 1 if the command is export or unset,
*	0 if not.
*/
static int	add_detail_quotes(char *command)
{
	return (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0);
}

/**
 *	Prints an error message to the standard error,
 *	prefixed with the program name.
 *	Returns with the specified error number.
 */
int	print_error(char *command, char *detail, char *error_message, int err)
{
	char	*msg;
	int		detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "`");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err);
}
