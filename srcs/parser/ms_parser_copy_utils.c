/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_copy_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:46 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:23 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_data_copy(char **dest, char *src)
{
	int	len;

	len = ft_strlen(src);
	if (len < 0)
		return (1);
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dest)
		return (1);
	while (len >= 0)
	{
		(*dest)[len] = src[len];
		len--;
	}
	return (0);
}

void	*free_old(t_liste *tmp)
{
	if (tmp)
	{
		if (tmp->start)
		{
			if (tmp->start->command)
				tmp->start->command = free_command(tmp->start->command);
			if (tmp->start->logicalexpression)
				tmp->start->logicalexpression = free_logical(\
				tmp->start->logicalexpression);
			if (tmp->start->pipeline)
				tmp->start->pipeline = free_pipe(tmp->start->pipeline);
			if (tmp->start->subshell)
				tmp->start->subshell = free_subshell(tmp->start->subshell);
		}
	}
	return (NULL);
}
