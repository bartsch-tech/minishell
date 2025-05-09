/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_copy1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:32 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:26 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical	*cp_logical(t_logical *cp)
{
	t_logical	*tmp;

	tmp = init_logical();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	tmp->op = cp->op;
	if (cp->left)
	{
		tmp->left = cp_liste(cp->left);
		if (!tmp->left)
			return (free_logical(tmp));
	}
	if (cp->right)
	{
		tmp->right = cp_liste(cp->right);
		if (!tmp->right)
			return (free_logical(tmp));
	}
	return (tmp);
}

t_subshell	*cp_subshell(t_subshell *cp)
{
	t_subshell	*tmp;

	tmp = init_subshell();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->liste)
	{
		tmp->liste = cp_liste(cp->liste);
		if (!tmp->liste)
			return (free_subshell(tmp));
	}
	return (tmp);
}

t_pipe	*cp_pipe(t_pipe *cp)
{
	t_pipe	*tmp;

	tmp = init_pipe();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->liste)
	{
		tmp->liste = cp_liste(cp->liste);
		if (!tmp->liste)
			return (free_pipe(tmp));
	}
	return (tmp);
}
