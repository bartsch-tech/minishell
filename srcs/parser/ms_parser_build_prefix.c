/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_prefix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:42 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees the prefix node and all its children
*/
void	*free_prefix(t_prefix *tmp)
{
	if (tmp)
	{
		if (tmp->text)
		{
			free(tmp->text);
			tmp->text = NULL;
		}
		if (tmp->expansion)
			tmp->expansion = free_expansion(tmp->expansion);
		if (tmp->op)
			tmp->op = free_op(tmp->op);
		if (tmp->file)
			tmp->file = free_file(tmp->file);
		if (tmp->next)
			tmp->next = free_prefix(tmp->next);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

static t_prefix	*add_redirect(t_prefix *tmp, t_token **token)
{
	if (!check_syntax(token))
		return (syntax_error_token(token, NULL));
	tmp->type = P_REDIRECT;
	tmp->op = op_node(token);
	tmp->file = file_node(token);
	if (!tmp->file || !tmp->op)
		return (free_prefix(tmp));
	return (tmp);
}

static t_prefix	*add_assign(t_prefix *tmp, t_token **token)
{
	tmp->type = P_ASSIGNMENT;
	tmp->text = ft_strdup((*token)->data);
	if (!tmp->text)
		return (free_prefix(tmp));
	if (has_expansion((*token)->data))
	{
		tmp->expansion = expansion_node((*token)->data, 0);
		if (!tmp->expansion)
			return (free_prefix(tmp));
	}
	return (tmp);
}

t_prefix	*prefix_node(t_token **token)
{
	t_prefix	*tmp;

	tmp = init_prefix();
	if (!tmp)
		return (NULL);
	if (is_redirect(ctt(token)))
	{
		tmp = add_redirect(tmp, token);
		if (!tmp)
			return (free_prefix(tmp));
	}
	else if (ctt(token) == T_ASSIGN)
	{
		tmp = add_assign(tmp, token);
		if (!tmp)
			return (free_prefix(tmp));
	}
	if (tmp && (ntt(token) == T_ASSIGN || is_redirect(ntt(token))))
	{
		*token = (*token)->next;
		tmp->next = prefix_node(token);
		if (!tmp->next)
			return (free_prefix(tmp));
	}
	return (tmp);
}
