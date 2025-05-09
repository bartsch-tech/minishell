/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:41 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:33 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_lst(char **lst)
{
	int	z;

	z = 0;
	while (lst && lst[z])
	{
		if (lst[z])
			free(lst[z]);
		z++;
	}
	free(lst);
	return (NULL);
}

int	dup_io(int in, int out)
{
	int	check;

	check = dup2(in, STDIN_FILENO);
	if (check == -1)
	{
		close(in);
		return (perror("dup input"), errno);
	}
	if (in != 0)
		close(in);
	check = dup2(out, STDOUT_FILENO);
	if (check == -1)
	{
		close(out);
		return (perror("dup output"), errno);
	}
	if (out != 1)
		close(out);
	return (0);
}

int	liste_type(t_liste *tmp)
{
	if (tmp)
	{
		if (tmp->start->command)
			return (P_COMMAND);
		else if (tmp->start->pipeline)
			return (P_PIPELINE);
		else if (tmp->start->subshell)
			return (P_SUBSHELL);
		else if (tmp->start->logicalexpression)
			return (P_LOGICALEXPRESSION);
	}
	return (P_ERROR);
}

char	**fill_lst(t_suffix *ptr, char **lst)
{
	int	z;

	z = 1;
	while (ptr)
	{
		if (ptr->text)
		{
			lst[z] = ft_strdup(ptr->text);
			if (!lst[z])
				return (NULL);
			z++;
		}
		ptr = ptr->next;
	}
	lst[z] = NULL;
	return (lst);
}
