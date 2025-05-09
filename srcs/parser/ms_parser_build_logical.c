/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_logical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:15 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:35 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a logical node
*/
void	*free_logical(t_logical *tmp)
{
	if (tmp)
	{
		if (tmp->left)
			tmp->left = free_liste(tmp->left);
		if (tmp->right)
			tmp->right = free_liste(tmp->right);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @file ms_parser_build_logical.c
 * @brief Builds a new logical node, and adds liste to the left
 * @return the new logical node
*/
t_logical	*logical_node(t_token **token, t_liste *left)
{
	t_logical	*tmp;
	t_liste		*cp;

	tmp = init_logical();
	if (!tmp)
		return (NULL);
	if (ctt(token) == T_AND)
		tmp->op = P_AND;
	else if (ctt(token) == T_OR)
		tmp->op = P_OR;
	cp = cp_liste(left);
	tmp->type = P_LOGICALEXPRESSION;
	if (!cp)
	{
		free_logical(tmp);
		free_liste(left);
		return (NULL);
	}
	tmp->left = cp;
	*token = (*token)->next;
	return (tmp);
}

/**
 * @file ms_parser_build_logical.c
 * @brief makes the first node a logicalexpression node
*/
static t_liste	*new_first(t_liste *first, t_logical *tmp)
{
	if (!tmp)
		return (free_liste(first));
	first->start->pipeline = NULL;
	first->start->subshell = NULL;
	first->start->command = NULL;
	first->start->logicalexpression = tmp;
	first->next = NULL;
	return (first);
}

/**
 * @file ms_parser_build_logical.c
 * @brief Builds a logical node with the left and right liste
*/
t_liste	*build_logical(t_token **token, t_liste *first, int is_subshell)
{
	t_logical	*tmp;

	tmp = logical_node(token, first);
	if (!tmp)
		return (free_liste(first));
	if (is_subshell)
		tmp->right = run_tokens_subshell_logical(token);
	else
		tmp->right = run_tokens_logical(token);
	if (!tmp->right)
		return (free_liste(first), free_logical(tmp));
	return (new_first(first, tmp));
}
