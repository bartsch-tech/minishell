/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_init2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:55:03 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:41 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes a new expansion node
*/
t_expansion	*init_expansion(void)
{
	t_expansion	*tmp;

	tmp = (t_expansion *)malloc(sizeof(t_expansion));
	if (!tmp)
		return (NULL);
	tmp->loc = NULL;
	tmp->parameter = NULL;
	tmp->type = -1;
	tmp->next = NULL;
	return (tmp);
}

/**
 * @file ms_parser_init2.c
 * @brief Initializes a new location node
*/
t_loc	*init_loc(void)
{
	t_loc	*tmp;

	tmp = (t_loc *)malloc(sizeof(t_loc));
	if (!tmp)
		return (NULL);
	tmp->start = -1;
	tmp->end = -1;
	return (tmp);
}

/**
 * @file ms_parser_init2.c
 * @brief Initializes a new command node
*/
t_command	*init_command(void)
{
	t_command	*tmp;

	tmp = (t_command *)malloc(sizeof(t_command));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->name = NULL;
	tmp->prefix = NULL;
	tmp->suffix = NULL;
	return (tmp);
}

/**
 * @file ms_parser_init2.c
 * @brief Initializes a new list node
*/
t_liste	*init_liste(void)
{
	t_liste	*tmp;

	tmp = (t_liste *)malloc(sizeof(t_liste));
	if (!tmp)
		return (NULL);
	tmp->type = -1;
	tmp->start = NULL;
	tmp->next = NULL;
	return (tmp);
}
