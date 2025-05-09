/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:20:55 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:54 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_subshell(t_subshell *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	ret = exp_liste(tmp->liste, env);
	return (ret);
}

int	exp_pipe(t_pipe *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	ret = exp_liste(tmp->liste, env);
	return (ret);
}

int	exp_logical(t_logical *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	ret = exp_liste(tmp->left, env);
	if (ret != 0)
		return (ret);
	ret = exp_liste(tmp->right, env);
	return (ret);
}

int	exp_command(t_command *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	if (tmp->prefix)
		ret = exp_prefix(tmp->prefix, env);
	if (ret != 0)
		return (ret);
	if (tmp->suffix)
		ret = exp_suffix(tmp->suffix, env);
	if (ret != 0)
		return (ret);
	if (tmp->name)
		ret = exp_name(tmp, env);
	if (ret != 0)
		return (ret);
	return (ret);
}

int	exp_liste(t_liste *liste, t_env *env)
{
	int	ret;

	ret = 0;
	while (liste)
	{
		if (liste->start->command)
			ret = exp_command(liste->start->command, env);
		if (liste->start->subshell)
			ret = exp_subshell(liste->start->subshell, env);
		if (liste->start->pipeline)
			ret = exp_pipe(liste->start->pipeline, env);
		if (liste->start->logicalexpression)
			ret = exp_logical(liste->start->logicalexpression, env);
		if (ret != 0)
			return (ret);
		liste = liste->next;
	}
	return (ret);
}
