/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:02 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/13 23:40:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char *envp[])
{
	t_env	*tmp;
	int		z;

	z = 0;
	while (envp[z])
		z++;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->env_g = (char **)malloc(sizeof(char *) * (z + 1));
	if (!tmp->env_g)
		return (free(tmp), NULL);
	tmp->ast = NULL;
	return (tmp);
}

void	free_env(t_env *tmp)
{
	if (tmp->env_g)
		free_lst(tmp->env_g);
	if (tmp->ast)
		free_root(tmp->ast);
	free(tmp);
}

int	cp_env(t_env *tmp, char *envp[])
{
	int	z;

	z = 0;
	while (envp && envp[z])
	{
		tmp->env_g[z] = ft_strdup(envp[z]);
		if (!tmp->env_g[z])
			return (free_env(tmp), errno);
		z++;
	}
	tmp->env_g[z] = NULL;
	return (0);
}

int	build_env(t_env **tmp, char *envp[])
{
	int	ret;

	ret = 0;
	*tmp = init_env(envp);
	ret = cp_env(*tmp, envp) != 0;
	if (ret != 0)
	{
		free_env(*tmp);
		tmp = NULL;
		return (ret);
	}
	return (ret);
}
