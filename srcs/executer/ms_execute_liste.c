/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_liste.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:09 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:09 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_liste(t_liste *tmp, int fd_in, int fd_out, t_env *env)
{
	int		ret;
	t_liste	*ptr;

	ret = 0;
	ptr = tmp;
	while (ptr)
	{
		if (liste_type(ptr) == P_COMMAND)
			ret = execute_command(ptr->start->command, fd_in, fd_out, env);
		else if (liste_type(ptr) == P_SUBSHELL)
			ret = execute_subshell(ptr->start->subshell, fd_in, fd_out, env);
		else if (liste_type(ptr) == P_PIPELINE)
			ret = execute_pipe(ptr->start->pipeline, fd_in, fd_out, env);
		else if (liste_type(ptr) == P_LOGICALEXPRESSION)
			ret = execute_logical(ptr->start->logicalexpression, fd_in, fd_out, \
			env);
		if (ret != 0)
			return (ret);
		ptr = ptr->next;
	}
	return (ret);
}
