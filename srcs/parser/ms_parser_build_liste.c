/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_liste.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:08 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:30 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief adds a list below a new list (start)
*/
t_liste	*cp_liste(t_liste *cp)
{
	t_liste	*tmp;

	tmp = init_liste();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->start)
	{
		tmp->start = cp_start(cp->start);
		if (!tmp->start)
			return (free_liste(tmp));
	}
	if (cp->next)
	{
		tmp->next = cp_liste(cp->next);
		if (!tmp->next)
			return (free_liste(tmp));
	}
	free_old(cp);
	return (tmp);
}

/**
 * @file ms_parser_build_liste.c
 * @brief Recursively frees the list
*/
void	*free_liste(t_liste *tmp)
{
	if (tmp)
	{
		if (tmp->start)
			tmp->start = free_start(tmp->start);
		if (tmp->next)
			tmp->next = free_liste(tmp->next);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @file ms_parser_build_liste.c
 * @brief Builds a new list node
 * @return A new, initialized list node with a start node.
*/
t_liste	*liste_node(void)
{
	t_liste	*tmp;

	tmp = init_liste();
	if (!tmp)
		return (NULL);
	tmp->start = init_start();
	if (!tmp->start)
		return (free_liste(tmp));
	tmp->type = P_LISTE;
	return (tmp);
}
