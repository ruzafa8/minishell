/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorilla <amorilla@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:14:26 by amorilla          #+#    #+#             */
/*   Updated: 2023/06/05 15:14:30 by amorilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

typedef enum e_parser_state
{
	PARS_START,
	PARS_COMMAND,
	PARS_REDIR_IN,
	PARS_REDIR_OUT,
	PARS_REDIR_OUT_APPEND,
	PARS_REDIR_IN_HEREDOC,
	PARS_INVALID
}	t_pars_st;

typedef enum e_parser_error
{
	PARS_NO_ERROR,
	PARS_SYNTAX_ERROR,
	PARS_MALLOC_ERROR,
	PARS_NO_SUCH_FILE_OR_DIR,
}	t_pars_err;

#endif