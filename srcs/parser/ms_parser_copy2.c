/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_copy2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:37 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:29 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_name	*cp_name(t_name *cp)
{
	t_name	*tmp;

	tmp = init_name();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->text)
		if (ms_data_copy(&tmp->text, cp->text))
			return (free_name(tmp));
	if (cp->expansion)
	{
		tmp->expansion = cp_expansion(cp->expansion);
		if (tmp->expansion)
			return (free_name(tmp));
	}
	return (tmp);
}

t_op	*cp_op(t_op *cp)
{
	t_op	*tmp;

	tmp = init_op();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->text)
		if (ms_data_copy(&tmp->text, cp->text))
			return (free_op(tmp));
	return (tmp);
}

t_file	*cp_file(t_file *cp)
{
	t_file	*tmp;

	tmp = init_file();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->text)
		if (ms_data_copy(&tmp->text, cp->text))
			return (free_file(tmp));
	if (cp->expansion)
	{
		tmp->expansion = cp_expansion(cp->expansion);
		if (!tmp->expansion)
			return (free_file(tmp));
	}
	return (tmp);
}

t_loc	*cp_loc(t_loc *cp)
{
	t_loc	*tmp;

	tmp = init_loc();
	if (!tmp)
		return (NULL);
	tmp->start = cp->start;
	tmp->end = cp->end;
	return (tmp);
}

t_expansion	*cp_expansion(t_expansion *cp)
{
	t_expansion	*tmp;

	tmp = init_expansion();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->parameter)
		if (ms_data_copy(&tmp->parameter, cp->parameter))
			return (free_expansion(tmp));
	if (cp->loc)
	{
		tmp->loc = cp_loc(cp->loc);
		if (!tmp->loc)
			return (free_expansion(tmp));
	}
	if (cp->next)
	{
		tmp->next = cp_expansion(cp->next);
		if (!tmp->next)
			return (free_expansion(tmp));
	}
	return (tmp);
}
