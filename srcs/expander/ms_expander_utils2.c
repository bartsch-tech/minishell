/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 22:22:43 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:05 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_suffix(t_suffix *old, t_suffix *new)
{
	t_suffix	*tmp;

	tmp = old;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
