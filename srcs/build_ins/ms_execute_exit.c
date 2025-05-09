/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:53:15 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_command *tmp, int in, int out, t_env *env)
{
	char	**ltmp;
	t_root	*atmp;

	ltmp = env->env_g;
	atmp = env->ast;
	if (tmp->prefix)
		execute_prefix(tmp->prefix, &in, &out, env);
	if (tmp->suffix)
		execute_suffix(tmp->suffix, &in, &out);
	dup_io(in, out);
	env->ast = free_root(atmp);
	env->env_g = free_lst(ltmp);
	free(env);
	exit(0);
}
