/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:18 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:15 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(t_token **token)
{
	if (is_sub(token) || is_sub_cl(token))
		return (1);
	else if (is_logical(token) || is_pipe(token))
		return (1);
	else
		return (0);
}

int	check_syntax2(t_token **token)
{
	if (token && *token && (*token)->next)
	{
		if (is_redirect(ctt(token)) && !is_word(ntt(token)))
			return (0);
	}
	return (1);
}

/**
 * @brief Checks if the input is syntactically possible,
 * e.g. "&& &&" is not possible
*/
int	check_syntax(t_token **token)
{
	if (token && *token && (*token)->next)
	{
		if (is_sub(token) && is_pipe(&(*token)->next))
			return (0);
		if (is_sub(token) && is_logical(&(*token)->next))
			return (0);
		if (is_logical(token) && is_pipe(&(*token)->next))
			return (0);
		if (is_logical(token) && is_logical(&(*token)->next))
			return (0);
		if (is_pipe(token) && is_pipe(&(*token)->next))
			return (0);
		if (is_pipe(token) && is_logical(&(*token)->next))
			return (0);
		if (is_command(token) && is_sub(&(*token)->next))
			return (0);
		if (is_op(token) && !ntt(token))
			return (0);
	}
	return (check_syntax2(token));
}

int	is_expandable(t_token **token)
{
	if (ctt(token) == T_DWORD)
	{
		if ((*token)->data[1])
			return (1);
	}
	return (0);
}

int	has_expansion(char *str)
{
	char	*ptr;

	ptr = str;
	while (ptr && *ptr)
	{
		if (*ptr == '$' && is_expansion(*(ptr + 1)))
			return (1);
		ptr++;
	}
	return (0);
}
