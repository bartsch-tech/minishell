/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:21 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:38 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a name node
*/
void	*free_name(t_name *tmp)
{
	if (tmp)
	{
		if (tmp->text)
		{
			free(tmp->text);
			tmp->text = NULL;
		}
		if (tmp->expansion)
			tmp->expansion = free_expansion(tmp->expansion);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @brief builds a new name node with the current data
*/
t_name	*name_node(t_token **token)
{
	t_name	*tmp;

	tmp = init_name();
	if (!tmp)
		return (NULL);
	if ((*token)->type == T_DWORD)
		tmp->type = P_XWORD;
	else
		tmp->type = P_WORD;
	tmp->text = ft_strdup((*token)->data);
	if ((*token)->type == T_DWORD)
	{
		tmp->expansion = expansion_node((*token)->data, 0);
		if (!tmp->expansion)
			return (free_name(tmp));
	}
	if (!tmp->text)
		return (free_name(tmp));
	return (tmp);
}
