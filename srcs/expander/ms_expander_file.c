/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:20:50 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:49 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_file(t_file *tmp, t_env *env)
{
	char	*ptr;
	char	*new;

	ptr = ms_getenv(tmp->expansion->parameter, env);
	new = ft_strdup(ptr);
	if (new != 0)
		return (errno);
	free(tmp->text);
	tmp->text = new;
	return (0);
}
