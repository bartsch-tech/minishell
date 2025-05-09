/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:14 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:11 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the token is a comment - word, redirect or assign
*/
int	is_command(t_token **token)
{
	if (is_word(ctt(token)))
		return (1);
	else if (is_redirect(ctt(token)))
		return (1);
	else if (ctt(token) == T_ASSIGN)
		return (1);
	else
		return (0);
}

/**
 * @brief Checks if the token is a subshell opening "C"
*/
int	is_sub(t_token **token)
{
	if (ctt(token) == T_BR_OP)
		return (1);
	else
		return (0);
}

/**
 * @brief Checks if the token is a logical operator "&&" or "||"
*/
int	is_logical(t_token **token)
{
	if (ctt(token) == T_AND)
		return (1);
	else if (ctt(token) == T_OR)
		return (1);
	else
		return (0);
}

/**
 * @brief Checks if the token is a pipe "|"
*/
int	is_pipe(t_token **token)
{
	if (ctt(token) == T_PIPE)
		return (1);
	else
		return (0);
}

/**
 * @brief Checks if the token is a subshell closing ")"
*/
int	is_sub_cl(t_token **token)
{
	if (ctt(token) == T_BR_CL)
		return (1);
	else
		return (0);
}
