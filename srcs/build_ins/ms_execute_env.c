/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:52:54 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:44 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_env(t_env *env)
{
	int		ret;
	char	**ptr;

	ret = 0;
	ptr = env->env_g;
	while (ptr && *ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	return (ret);
}

int	execute_env(t_command *tmp, int in, int out, t_env *env)
{
	int		ret;

	ret = 0;
	if (tmp->prefix)
		ret = execute_prefix(tmp->prefix, &in, &out, env);
	if (ret != 0)
		return (ret);
	if (tmp->suffix)
		ret = execute_suffix(tmp->suffix, &in, &out);
	if (ret != 0)
		return (ret);
	ret = dup_io(in, out);
	if (ret != 0)
		return (ret);
	ret = handle_env(env);
	return (ret);
}
