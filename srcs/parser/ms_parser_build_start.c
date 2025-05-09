/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:53:52 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:57 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_start(t_start *tmp)
{
	if (tmp)
	{
		if (tmp->command)
			tmp->command = free_command(tmp->command);
		if (tmp->logicalexpression)
			tmp->logicalexpression = free_logical(tmp->logicalexpression);
		if (tmp->subshell)
			tmp->subshell = free_subshell(tmp->subshell);
		if (tmp->pipeline)
			tmp->pipeline = free_pipe(tmp->pipeline);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

t_start	*cp_start2(t_start *cp, t_start *tmp)
{
	if (cp->pipeline)
	{
		tmp->pipeline = cp_pipe(cp->pipeline);
		if (!tmp->pipeline)
			return (free_start(tmp));
	}
	else if (cp->subshell)
	{
		tmp->subshell = cp_subshell(cp->subshell);
		if (!tmp->subshell)
			return (free_start(tmp));
	}
	return (tmp);
}

t_start	*cp_start(t_start *cp)
{
	t_start	*tmp;

	tmp = init_start();
	if (!tmp)
		return (NULL);
	if (cp->command)
	{
		tmp->command = cp_command(cp->command);
		if (!tmp->command)
			return (free_start(tmp));
	}
	else if (cp->logicalexpression)
	{
		tmp->logicalexpression = cp_logical(cp->logicalexpression);
		if (!tmp->logicalexpression)
			return (free_start(tmp));
	}
	else if (cp->pipeline || cp->subshell)
		tmp = cp_start2(cp, tmp);
	return (tmp);
}
