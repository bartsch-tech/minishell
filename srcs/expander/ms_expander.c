/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:55:08 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:07 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander_main(t_root *ast, t_env *env)
{
	int	ret;

	ret = 0;
	if (!ast && !ast->liste)
		return (-1);
	ret = exp_liste(ast->liste, env);
	if (ret != 0)
		return (free_root(ast), ret);
	return (ret);
}
