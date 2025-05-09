/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:27 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:58 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief move to the next token in the list
*/
int	next_token(t_token **token)
{
	if (check_syntax(token))
	{
		*token = (*token)->next;
		return (1);
	}
	if ((*token)->next == T_NULL)
		*token = (*token)->next;
	return (0);
}

static void	free_tokenlist(t_lltoken *lst)
{
	t_token	*tmp;
	t_token	*frees;

	tmp = lst->lltoken;
	while (tmp)
	{
		frees = tmp;
		tmp = tmp->next;
		free(frees->data);
		free(frees);
	}
}

// @file ms_parser.c
// @brief Contains functions for parsing input linked token
// token and building an abstract syntax tree.
// @param *lst Linked list of tokens.
// @return Pointer to root node of abstract syntax tree.

int	parser_main(t_lltoken *lst, t_root **ast)
{
	t_token	*token;
	t_root	*root;

	*ast = NULL;
	if (!lst && !lst->lltoken)
		return (-1);
	token = lst->lltoken;
	root = root_node();
	if (!root)
		return (-1);
	root->liste = run_tokens(&token);
	if (!root->liste)
		return (free_root(root), 2);
	free_tokenlist(lst);
	*ast = root;
	return (0);
}
