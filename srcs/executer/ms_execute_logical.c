/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_logical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:13 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/13 19:47:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	op_type(t_logical *tmp)
{
	if (tmp)
		return (tmp->op);
	return (P_ERROR);
}

int	execute_logical(t_logical *tmp, int fd_in, int fd_out, t_env *env)
{
	int	ret;

	ret = 0;
	ret = execute_liste(tmp->left, fd_in, fd_out, env);
	if (ret == 0 && op_type(tmp) == P_AND)
		ret = execute_liste(tmp->right, fd_in, fd_out, env);
	else if (ret != 0 && op_type(tmp) == P_OR)
		ret = execute_liste(tmp->right, fd_in, fd_out, env);
	else
		return (ret);
	return (ret);
}
