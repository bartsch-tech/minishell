/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_empty_command.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:29 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:21 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief creates an empty name node
*/
static t_name	*empty_name_node(void)
{
	t_name	*tmp;

	tmp = init_name();
	tmp->type = P_WORD;
	tmp->text = (char *)malloc(sizeof(char));
	if (!tmp->text)
	{
		free(tmp);
		return (NULL);
	}
	tmp->text[0] = '\0';
	return (tmp);
}

/**
 * @brief creates an empty command node
 * @param pre the prefix node
 * @return t_command node initialized, with prefix and empty name
*/
t_command	*empty_command_node(t_prefix *pre)
{
	t_command	*tmp;

	tmp = init_command();
	if (!tmp)
		return (NULL);
	tmp->type = P_COMMAND;
	tmp->name = empty_name_node();
	tmp->prefix = pre;
	if (!tmp->prefix)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
