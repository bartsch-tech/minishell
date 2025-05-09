/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:29:32 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/13 23:30:25 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds token node to the end of the linked list
*/
void	lstadd_back(t_lltoken **list, t_token *add)
{
	t_token	*tmp;

	if (!(*list)->lltoken)
		(*list)->lltoken = add;
	else
	{
		tmp = (*list)->lltoken;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
}

/**
 * @brief Frees linked list starting and including first token
*/
void	llist_free(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->data);
		free(token);
		token = tmp;
	}
}

/**
 * @brief Prints list connected to token head
*/
void	print_llist(t_lltoken token_head)
{
	t_token	*token;

	token = token_head.lltoken;
	while (token)
	{
		printf("String: '%s'\t\t\tType: %d\n", token->data, token->type);
		token = token->next;
	}
}
