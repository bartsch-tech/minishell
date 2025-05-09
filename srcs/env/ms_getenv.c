/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:19 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:24 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char	*str, t_env *env)
{
	char	**ptr;

	ptr = env->env_g;
	while (*ptr)
	{
		if (ft_memcmp(*ptr, str, ft_strlen(str)) == 0 && \
			(*ptr)[ft_strlen(str)] == '=')
			return (ft_strdup(&(*ptr)[ft_strlen(str) + 1]));
		ptr++;
	}
	return (NULL);
}
