/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_init1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:56 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:38 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_logical	*init_logical(void)
{
	t_logical	*tmp;

	tmp = (t_logical *)malloc(sizeof(t_logical));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->op = -1;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

t_subshell	*init_subshell(void)
{
	t_subshell	*tmp;

	tmp = (t_subshell *)malloc(sizeof(t_subshell));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->liste = NULL;
	return (tmp);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*tmp;

	tmp = (t_pipe *)malloc(sizeof(t_pipe));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->liste = NULL;
	return (tmp);
}

/**
 * @file ms_parser_init1.c
 * @brief Initializes the root node for the parser tree.
 */
t_root	*init_root(void)
{
	t_root	*tmp;

	tmp = (t_root *)malloc(sizeof(t_root));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->liste = NULL;
	return (tmp);
}

/**
 * @file ms_parser_init1.c
 * @brief Initializes the start node for the list node.
 * @return t_start node with all values set to NULL.
 */
t_start	*init_start(void)
{
	t_start	*tmp;

	tmp = (t_start *)malloc(sizeof(t_start));
	if (!tmp)
		return (NULL);
	tmp->command = NULL;
	tmp->pipeline = NULL;
	tmp->subshell = NULL;
	tmp->logicalexpression = NULL;
	return (tmp);
}
