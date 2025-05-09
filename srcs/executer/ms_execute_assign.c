/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:49 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:56 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_assign(char *str)
{
	char	**lst;

	lst = ft_split(str, '=');
	if (!str)
		return (-1);
	free(str);
	free_lst(lst);
	return (0);
}
