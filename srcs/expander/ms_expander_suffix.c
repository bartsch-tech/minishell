/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:21:05 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:00 by mgraf            ###   ########.fr       */
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

static int	exp_dollar(t_suffix *tmp, t_env *env)
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

int	exp_decide(t_suffix *tmp, t_env *env)
{
	if (tmp->expansion)
		return (exp_dollar(tmp, env));
	else if (has_asterix(tmp->text))
		return (exp_asterix(tmp));
	else
		return (0);
}

int	exp_suffix(t_suffix *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	while (tmp)
	{
		if (exp_type(tmp->type))
		{
			ret = exp_decide(tmp, env);
			if (tmp->expansion)
				tmp->expansion = free_expansion(tmp->expansion);
			else if (tmp->file && tmp->file->expansion)
			{
				ret = exp_file(tmp->file, env);
				tmp->file->expansion = free_expansion(tmp->file->expansion);
			}
		}
		if (ret != 0)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}
