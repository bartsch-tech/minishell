/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:45:47 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:20 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_suffix(int type)
{
	if (is_word(type))
		return (1);
	if (is_redirect(type))
		return (1);
	if (type == T_ASSIGN)
		return (1);
	return (0);
}
