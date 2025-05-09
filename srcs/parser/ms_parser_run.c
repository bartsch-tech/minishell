/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:55:21 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:54 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file ms_parser_run.c
 * @brief Runs the parser.
 * @details Parent of recursive	functions that build the tree.
 * @param token The token list.
 * @return The node to be appened to the list calling it.
*/
t_liste	*run_tokens(t_token **token)
{
	t_liste	*tmp;

	tmp = liste_node();
	if (!tmp)
		return (free_liste(tmp));
	while (*token && (*token)->type)
	{
		if (!check_syntax(token))
			return (syntax_error_token(token, tmp));
		if (is_command(token))
			tmp = build_command(token, tmp);
		else if (is_pipe(token) && next_token(token))
			tmp = build_pipe(token, tmp);
		else if (is_logical(token) && ntt(token))
			tmp = build_logical(token, tmp, 0);
		else if (is_sub(token) && next_token(token))
			tmp = build_subshell(token, tmp);
		if (!tmp)
			return (free_liste(tmp));
		if (*token && is_sub_cl(token))
			(*token) = (*token)->next;
	}
	return (tmp);
}

t_liste	*run_tokens_subshell(t_token **token)
{
	t_liste	*tmp;

	tmp = liste_node();
	if (!tmp)
		return (free_liste(tmp));
	while (*token && (*token)->type && !is_sub_cl(token))
	{
		if (!check_syntax(token))
			return (syntax_error_token(token, tmp));
		if (is_command(token))
			tmp = build_command(token, tmp);
		else if (is_pipe(token) && next_token(token))
			tmp = build_pipe(token, tmp);
		else if (is_logical(token) && ntt(token))
			tmp = build_logical(token, tmp, 1);
		else if (is_sub(token) && next_token(token))
			tmp = build_subshell(token, tmp);
		if ((!is_sub_cl(token)) && ctt(token) == T_NULL)
			return (error_bracket_close(tmp));
		if (!tmp)
			return (free_liste(tmp));
	}
	if (is_sub_cl(token))
		*token = (*token)->next;
	return (tmp);
}

t_liste	*run_tokens_subshell_logical(t_token **token)
{
	t_liste	*tmp;

	tmp = liste_node();
	if (!tmp)
		return (free_liste(tmp));
	while (*token && (*token)->type && !is_sub_cl(token))
	{
		if (!check_syntax(token))
			return (syntax_error_token(token, tmp));
		if (is_command(token))
			tmp = build_command(token, tmp);
		else if (is_pipe(token) && next_token(token))
			tmp = build_pipe(token, tmp);
		else if (is_logical(token) && ntt(token))
			tmp = build_logical(token, tmp, 1);
		else if (is_sub(token) && next_token(token))
			tmp = build_subshell(token, tmp);
		if (!tmp)
			return (free_liste(tmp));
	}
	return (tmp);
}

t_liste	*run_tokens_logical(t_token **token)
{
	t_liste	*tmp;

	tmp = liste_node();
	if (!tmp)
		return (free_liste(tmp));
	while (*token && (*token)->type && !is_logical(token))
	{
		if (!check_syntax(token))
			return (syntax_error_token(token, tmp));
		if (is_command(token))
			tmp = build_command(token, tmp);
		else if (is_pipe(token) && next_token(token))
			tmp = build_pipe(token, tmp);
		else if (is_logical(token) && ntt(token))
			tmp = build_logical(token, tmp, 0);
		else if (is_sub(token) && next_token(token))
		{
			tmp = build_subshell(token, tmp);
			next_token(token);
		}
		if (!tmp)
			return (free_liste(tmp));
	}
	return (tmp);
}
