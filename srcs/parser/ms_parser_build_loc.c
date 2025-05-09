/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_loc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:12 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/13 22:10:31 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a loc node
*/
void	*free_loc(t_loc *tmp)
{
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @file ms_parser_build_loc.c
 * @brief Builds a new loc node
 * @param start the start of the location
 * @param end the end of the location
 * @return the new loc node
*/
t_loc	*loc_node(int start, int end)
{
	t_loc	*tmp;

	tmp = (t_loc *)malloc(sizeof(t_loc));
	if (!tmp)
		return (NULL);
	tmp->start = start;
	tmp->end = end;
	return (tmp);
}
