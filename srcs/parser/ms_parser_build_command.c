/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:22 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:18 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief frees a command node, with prefix, name and suffix
*/
void	*free_command(t_command *tmp)
{
	if (tmp)
	{
		if (tmp->name)
			tmp->name = free_name(tmp->name);
		if (tmp->prefix)
			tmp->prefix = free_prefix(tmp->prefix);
		if (tmp->suffix)
			tmp->suffix = free_suffix(tmp->suffix);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

/**
 * @file ms_parser_build_command.c
 * @brief Builds a new command node.
*/
t_command	*command_node(t_token **token, t_prefix *pre)
{
	t_command	*tmp;

	tmp = init_command();
	if (!tmp)
		return (NULL);
	tmp->type = P_COMMAND;
	tmp->name = name_node(token);
	if (pre)
		tmp->prefix = pre;
	if (is_word(ntt(token)) || is_redirect(ntt(token)) \
		|| ntt(token) == T_ASSIGN)
	{
		*token = (*token)->next;
		tmp->suffix = suffix_node(token);
		if (!tmp->suffix)
			return (free_command(tmp));
	}
	if (!tmp->name)
		return (free_command(tmp));
	return (tmp);
}

/**
 * @file ms_parser_build_command.c
 * @brief Attaches a command node to the list given
*/
static t_liste	*new_first(t_token **token, t_liste *first, t_command *tmp)
{
	next_token(token);
	if (!tmp)
		return (free_liste(first));
	first->start->subshell = NULL;
	first->start->logicalexpression = NULL;
	first->start->pipeline = NULL;
	first->start->command = tmp;
	first->next = NULL;
	return (first);
}

/**
 * @file ms_parser_build_command.c
 * @brief Builds a new command node, also a prefix if needed
*/
t_liste	*build_command(t_token **token, t_liste *first)
{
	t_command	*tmp;
	t_prefix	*pre;

	tmp = NULL;
	if (is_redirect(ctt(token)) || ctt(token) == T_ASSIGN)
	{
		pre = prefix_node(token);
		if (!pre)
			return (free_liste(first), free_command(tmp));
		if (is_word(ntt(token)))
		{
			*token = (*token)->next;
			return (new_first(token, first, command_node(token, pre)));
		}
		else
			return (new_first(token, first, empty_command_node(pre)));
	}
	else
	{
		pre = NULL;
		return (new_first(token, first, command_node(token, pre)));
	}
}
