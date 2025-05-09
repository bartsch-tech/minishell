/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_subshell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:02 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_subshell(t_subshell *tmp)
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

t_subshell	*subshell_node(void)
{
	t_subshell	*tmp;

	tmp = init_subshell();
	if (!tmp)
		return (NULL);
	tmp->type = P_SUBSHELL;
	return (tmp);
}

static t_liste	*new_first(t_liste *first, t_subshell *tmp)
{
	if (!tmp)
		return (free_liste(first));
	first->start->logicalexpression = NULL;
	first->start->pipeline = NULL;
	first->start->command = NULL;
	first->start->subshell = tmp;
	first->next = NULL;
	return (first);
}

t_liste	*build_subshell(t_token **token, t_liste *first)
{
	t_subshell	*tmp;

	tmp = subshell_node();
	if (!tmp)
		return (free_liste(first), free_liste(first));
	tmp->liste = run_tokens_subshell(token);
	if (!tmp->liste)
		return (free_liste(first), free_subshell(tmp));
	return (new_first(first, tmp));
}
