/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:25 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/13 19:51:18 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirect(t_op **op, t_file **file, int *fd_in, int *fd_out)
{
	if (ft_memcmp((*op)->text, ">", 2) == 0)
		*fd_out = open((*file)->text, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (ft_memcmp((*op)->text, ">>", 3) == 0)
		*fd_out = open((*file)->text, O_APPEND | O_CREAT | O_WRONLY, 0644);
	else
		*fd_in = open((*file)->text, O_RDONLY);
	if ((*fd_in) == -1)
		return (print_error((*file)->text, ": ", strerror(errno)), errno);
	if ((*fd_out) == -1)
		return (print_error((*file)->text, ": ", strerror(errno)), errno);
	*file = free_file(*file);
	*op = free_op(*op);
	return (0);
}
