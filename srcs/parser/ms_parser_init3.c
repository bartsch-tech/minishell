/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_init3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:55:09 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:45 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_suffix	*init_suffix(void)
{
	t_suffix	*tmp;

	tmp = (t_suffix *)malloc(sizeof(t_suffix));
	if (!tmp)
		return (NULL);
	tmp->text = NULL;
	tmp->expansion = NULL;
	tmp->type = -1;
	tmp->op = NULL;
	tmp->file = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_prefix	*init_prefix(void)
{
	t_prefix	*tmp;

	tmp = (t_prefix *)malloc(sizeof(t_prefix));
	if (!tmp)
		return (NULL);
	tmp->text = NULL;
	tmp->expansion = NULL;
	tmp->type = -1;
	tmp->op = NULL;
	tmp->file = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_file	*init_file(void)
{
	t_file	*tmp;

	tmp = (t_file *)malloc(sizeof(t_file));
	if (!tmp)
		return (NULL);
	tmp->text = NULL;
	tmp->expansion = NULL;
	tmp->type = -1;
	return (tmp);
}

/**
 * @file ms_parser_init3.c
 * @brief Initializes a new op node
*/
t_op	*init_op(void)
{
	t_op	*tmp;

	tmp = (t_op *)malloc(sizeof(t_op));
	if (!tmp)
		return (NULL);
	tmp->text = NULL;
	tmp->type = -1;
	return (tmp);
}

/**
 * @file ms_parser_init3.c
 * @brief Initializes a new name node
 * @return t_name* - the new name node
*/

t_name	*init_name(void)
{
	t_name	*tmp;

	tmp = (t_name *)malloc(sizeof(t_name));
	if (!tmp)
		return (NULL);
	tmp->text = NULL;
	tmp->expansion = NULL;
	tmp->type = -1;
	return (tmp);
}
