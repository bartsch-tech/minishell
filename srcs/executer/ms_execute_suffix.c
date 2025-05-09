/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_suffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:33 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:30 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ant(t_suffix *tmp)
{
	if (tmp)
		return (tmp->type);
	return (0);
}

int	execute_suffix(t_suffix *tmp, int *fd_in, int *fd_out)
{
	int	ret;

	ret = 0;
	if (ant(tmp) == P_REDIRECT)
		ret = execute_redirect(&tmp->op, &tmp->file, fd_in, fd_out);
	if (ret != 0)
		return (ret);
	if (tmp->next)
		ret = execute_suffix(tmp->next, fd_in, fd_out);
	return (ret);
}
