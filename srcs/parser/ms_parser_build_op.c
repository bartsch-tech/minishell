/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_op.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:33 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:41 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees an operator node
*/
void	*free_op(t_op *tmp)
{
	if (tmp)
	{
		if (tmp->text)
		{
			free(tmp->text);
			tmp->text = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @brief builds a new operator node with the current data
*/
t_op	*op_node(t_token **token)
{
	t_op	*tmp;
	int		type;

	tmp = init_op();
	if (!tmp)
		return (NULL);
	type = ctt(token);
	if (type == T_RE_IN)
		tmp->type = P_LESS;
	else if (type == T_RE_OUT)
		tmp->type = P_GREAT;
	else if (type == T_AP_OUT)
		tmp->type = P_DGREAT;
	tmp->text = ft_strdup((*token)->data);
	if (!tmp->text)
		return (free_op(tmp));
	return (tmp);
}
