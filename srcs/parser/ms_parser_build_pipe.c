/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:38 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:43 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a pipe node
*/
void	*free_pipe(t_pipe *tmp)
{
	if (tmp)
	{
		if (tmp->liste)
			tmp->liste = free_liste(tmp->liste);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @file ms_parser_build_pipe.c
 * @brief Builds a new pipe node
*/
t_pipe	*pipe_node(void)
{
	t_pipe	*tmp;

	tmp = init_pipe();
	if (!tmp)
		return (NULL);
	tmp->type = P_PIPELINE;
	return (tmp);
}

/**
 * @file ms_parser_build_pipe.c
 * @brief Appends a list to a pipe node
*/
int	append_pipe(t_pipe **tmp, t_liste *new)
{
	t_liste	*cp;
	t_liste	*iter;

	cp = cp_liste(new);
	if (!cp)
	{
		free_liste(cp);
		return (0);
	}
	if (!(*tmp)->liste)
		(*tmp)->liste = cp;
	else
	{
		iter = (*tmp)->liste;
		while (iter->next)
			iter = iter->next;
		iter->next = cp;
	}
	return (1);
}

/**
 * @file ms_parser_build_pipe.c
 * @brief Attaches a pipe node to a list node
*/
static t_liste	*new_first(t_liste *first, t_pipe *tmp)
{
	if (!tmp)
		return (free_liste(first));
	first->start->command = NULL;
	first->start->subshell = NULL;
	first->start->logicalexpression = NULL;
	first->start->pipeline = tmp;
	first->next = NULL;
	return (first);
}

/**
 * @file ms_parser_build_pipe.c
 * @brief Builds a pipe node
*/
t_liste	*build_pipe(t_token **token, t_liste *first)
{
	t_pipe	*tmp;

	tmp = pipe_node();
	if (!tmp)
		return (free_liste(first));
	if (!append_pipe(&tmp, first))
		return (free_liste(first), free_pipe(tmp));
	while (is_pipe(token) || is_command(token) || is_sub(token))
	{
		if (!check_syntax(token))
			return (syntax_error_token(token, first));
		if (is_command(token))
		{
			if (!append_pipe(&tmp, build_command(token, first)))
				return (free_liste(first), free_pipe(tmp));
		}
		else if (is_sub(token) && next_token(token))
		{
			if (!append_pipe(&tmp, build_subshell(token, first)))
				return (free_liste(first), free_pipe(tmp));
		}
		if (is_pipe(token))
			next_token(token);
	}
	return (new_first(first, tmp));
}
