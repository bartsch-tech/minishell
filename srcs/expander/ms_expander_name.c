/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <mbartsch@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:18:29 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 13:39:36 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_len(t_expansion *tmp, int move)
{
	while (tmp)
	{
		tmp->loc->start += move;
		tmp->loc->end += move;
		tmp = tmp->next;
	}
	return (1);
}

static int	exp_dollar(t_name *tmp, t_env *env)
{
	char		*tmp_str;
	t_expansion	*ptr;
	int			move;

	move = 0;
	ptr = tmp->expansion;
	while (ptr)
	{
		tmp_str = ptr->parameter;
		tmp_str = ms_getenv(tmp_str, env);
		move = exp_insert(&tmp->text, tmp_str, ptr->loc->start, ptr->loc->end);
		if (!(move == -1) && ptr->next)
			add_new_len(ptr->next, move);
		ptr = ptr->next;
	}
	return (0);
}

int	exp_name(t_command *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	if (tmp)
	{
		if (exp_type(tmp->name->type))
		{
			if (tmp->name->expansion)
			{
				ret = exp_dollar(tmp->name, env);
				tmp->name->expansion = free_expansion(tmp->name->expansion);
			}
		}
		if (ret != 0)
			return (ret);
	}
	return (ret);
}
