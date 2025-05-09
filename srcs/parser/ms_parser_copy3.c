/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_copy3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:41 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:32 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_suffix	*cp_suffix2(t_suffix *cp, t_suffix *tmp)
{
	if (cp->op)
	{
		tmp->op = cp_op(cp->op);
		if (!tmp->op)
			return (free_suffix(tmp));
	}
	if (cp->file)
	{
		tmp->file = cp_file(cp->file);
		if (!tmp->file)
			return (free_suffix(tmp));
	}
	if (cp->next)
	{
		tmp->next = cp_suffix(cp->next);
		if (!tmp->next)
			return (free_suffix(tmp));
	}
	return (tmp);
}

t_suffix	*cp_suffix(t_suffix *cp)
{
	t_suffix	*tmp;

	tmp = init_suffix();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->text)
		if (ms_data_copy(&tmp->text, cp->text))
			return (free_suffix(tmp));
	if (cp->expansion)
	{
		tmp->expansion = cp_expansion(cp->expansion);
		if (!tmp->expansion)
			return (free_suffix(tmp));
	}
	tmp = cp_suffix2(cp, tmp);
	return (tmp);
}

t_prefix	*cp_prefix2(t_prefix *cp, t_prefix *tmp)
{
	if (cp->op)
	{
		tmp->op = cp_op(cp->op);
		if (!tmp->op)
			return (free_prefix(tmp));
	}
	if (cp->file)
	{
		tmp->file = cp_file(cp->file);
		if (!tmp->file)
			return (free_prefix(tmp));
	}
	if (cp->next)
	{
		tmp->next = cp_prefix(cp->next);
		if (!tmp->next)
			return (free_prefix(tmp));
	}
	return (tmp);
}

t_prefix	*cp_prefix(t_prefix *cp)
{
	t_prefix	*tmp;

	tmp = init_prefix();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->text)
		if (ms_data_copy(&tmp->text, cp->text))
			return (free_prefix(tmp));
	if (cp->expansion)
	{
		tmp->expansion = cp_expansion(cp->expansion);
		if (!tmp->expansion)
			return (free_prefix(tmp));
	}
	tmp = cp_prefix2(cp, tmp);
	return (tmp);
}

t_command	*cp_command(t_command *cp)
{
	t_command	*tmp;

	tmp = init_command();
	if (!tmp)
		return (NULL);
	tmp->type = cp->type;
	if (cp->name)
	{
		tmp->name = cp_name(cp->name);
		if (!tmp->name)
			return (free_command(tmp));
	}
	if (cp->suffix)
	{
		tmp->suffix = cp_suffix(cp->suffix);
		if (!tmp->suffix)
			return (free_command(tmp));
	}
	if (cp->prefix)
	{
		tmp->prefix = cp_prefix(cp->prefix);
		if (!tmp->prefix)
			return (NULL);
	}
	return (tmp);
}
