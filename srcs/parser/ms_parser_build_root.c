/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_root.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:46 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:50 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_root(t_root *tmp)
{
	if (tmp)
	{
		if (tmp->liste)
			tmp->liste = free_liste(tmp->liste);
		free (tmp);
		tmp = NULL;
	}
	return (tmp);
}

// @file ms_parser_build_root.c
// @brief Contains functions for building the root node
// of the minishell parser tree.
t_root	*root_node(void)
{
	t_root	*tmp;

	tmp = init_root();
	if (!tmp)
		return (NULL);
	tmp->type = P_ROOT;
	return (tmp);
}
