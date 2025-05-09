/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:54:40 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:34 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s1, char *s2, char *s3)
{
	write(2, "ms: ", 4);
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
	{
		write(2, s2, ft_strlen(s2));
		write(2, ": ", 2);
	}
	if (s3)
		write(2, s3, ft_strlen(s3));
	write(2, "\n", 1);
}
