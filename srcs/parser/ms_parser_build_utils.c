/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:24 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:08 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the token is of type word
 * @return 1 if token is a normal word, 2 if token is a dollar word,
 * 		3 if token is asterix word, 0 if not
*/
int	is_word(int type)
{
	if (type == T_NWORD)
		return (1);
	else if (type == T_DWORD)
		return (2);
	else if (type == T_AWORD)
		return (3);
	else
		return (0);
}

/**
 * @brief Checks if the token is of type redirect
 * @return 1 if token is a redirect in, 2 if token is a redirect out,
 * 		3 if token is append out, 0 if not
*/
int	is_redirect(int type)
{
	if (type == T_RE_IN)
		return (1);
	else if (type == T_RE_OUT)
		return (2);
	else if (type == T_AP_OUT)
		return (3);
	else
		return (0);
}

/**
 * @brief Next token type
 * @return type of next token or -1 if next token is NULL
*/
int	ntt(t_token **token)
{
	if (token)
		if (*token && (*token)->next)
			return ((*token)->next->type);
	return (-1);
}

/**
 * ctt = current token type
 * @return: type of current token or -1 if token is NULL
*/
int	ctt(t_token **token)
{
	if (token)
		if (*token)
			return ((*token)->type);
	return (-1);
}

int	type_liste(t_liste *tmp)
{
	if (tmp->start->command)
		return (P_COMMAND);
	else if (tmp->start->subshell)
		return (P_SUBSHELL);
	else if (tmp->start->pipeline)
		return (P_PIPELINE);
	else if (tmp->start->logicalexpression)
		return (P_LOGICALEXPRESSION);
	else
		return (-1);
}
