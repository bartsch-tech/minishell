/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:12 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:18 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cp_lst(char **cp)
{
	char	**tmp;
	int		z;

	z = 0;
	while (cp[z])
		z++;
	tmp = (char **)malloc(sizeof(char *) * (z + 1));
	if (!tmp)
		return (NULL);
	z = 0;
	while (cp && cp[z])
	{
		tmp[z] = ft_strdup(cp[z]);
		if (!tmp[z])
			return (free_lst(tmp));
		z++;
	}
	tmp[z] = NULL;
	return (tmp);
}

char	**sort_env(t_env *env)
{
	char	**prnt;
	int		z;
	int		z2;
	int		len;

	len = 0;
	z = 0;
	prnt = cp_lst(env->env_g);
	if (!prnt)
		return (NULL);
	while (prnt[len])
		len++;
	while (z < len - 1)
	{
		z2 = 0;
		while (z2 < len - z - 1)
		{
			if (ft_strcmp(prnt[z2], prnt[z2 + 1]) > 0)
				swap_ptr(&prnt[z2], &prnt[z2 + 1]);
			z2++;
		}
		z++;
	}
	return (prnt);
}
