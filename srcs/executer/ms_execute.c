/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:59 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:40 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executer_main(t_root *ast, t_env *env)
{
	int		ret;
	char	*str;
	char	*ret_str;

	if (!ast)
		return (-1);
	ret = 0;
	if (ast->liste)
		ret = execute_liste(ast->liste, 0, 1, env);
	ret_str = ft_itoa(ret);
	if (ret_str)
	{
		str = ft_strjoin("?=", ret_str);
		if (str)
		{
			ms_setenv(str, env);
			free(str);
		}
		free(ret_str);
	}
	return (free_root(ast), ret);
}
