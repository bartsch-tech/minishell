/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_suffix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:09 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:04 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a suffix node and all its children
*/
void	*free_suffix(t_suffix *tmp)
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
			tmp->next = free_suffix(tmp->next);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

static t_suffix	*add_redirect(t_suffix *tmp, t_token **token)
{
	tmp->type = P_REDIRECT;
	tmp->op = op_node(token);
	tmp->file = file_node(token);
	if (!tmp->file || !tmp->op)
		return (free_suffix(tmp));
	return (tmp);
}

static t_suffix	*add_word(t_suffix *tmp, t_token **token)
{
	if (ctt(token) == T_NWORD || ctt(token) == T_ASSIGN)
		tmp->type = P_WORD;
	else if (ctt(token) == T_DWORD || ctt(token) == T_AWORD)
		tmp->type = P_XWORD;
	tmp->text = ft_strdup((*token)->data);
	if (!tmp->text)
		return (free_suffix(tmp));
	return (tmp);
}

t_suffix	*suffix_node(t_token **token)
{
	t_suffix	*tmp;

	tmp = init_suffix();
	if (!tmp)
		return (NULL);
	if (is_redirect(ctt(token)))
		tmp = add_redirect(tmp, token);
	else if (is_word(ctt(token)) || ctt(token) == T_ASSIGN)
	{
		tmp = add_word(tmp, token);
		if (is_expandable(token))
		{
			tmp->expansion = expansion_node((*token)->data, 0);
			if (!tmp->expansion)
				return (free_suffix(tmp));
		}
	}
	if (tmp && is_suffix(ntt(token)))
	{
		*token = (*token)->next;
		tmp->next = suffix_node(token);
		if (!tmp->next)
			return (free_suffix(tmp));
	}
	return (tmp);
}
