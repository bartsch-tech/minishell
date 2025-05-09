/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:02:49 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:27 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_new_env(t_env *env)
{
	char	**tmp;
	int		z;

	z = 0;
	while (env->env_g && env->env_g[z])
		z++;
	tmp = (char **)malloc(sizeof(char *) * (z + 2));
	if (!tmp)
		return (NULL);
	z = 0;
	while (env->env_g && env->env_g[z])
	{
		tmp[z] = ft_strdup(env->env_g[z]);
		if (!tmp[z])
			return (free_lst(tmp));
		z++;
	}
	tmp[z] = NULL;
	return (tmp);
}

static int	replace_var(char *str, t_env *env)
{
	char	*key;
	char	**ptr;

	key = get_key(str);
	ptr = env->env_g;
	if (!key)
		return (errno);
	while (ptr && *ptr)
	{
		if (ft_memcmp(key, *ptr, ft_strlen(key)) == 0)
		{
			free(*ptr);
			*ptr = ft_strdup(str);
			free(key);
			if (!ptr)
				return (errno);
			return (0);
		}
		ptr++;
	}
	free(key);
	return (1);
}

int	ms_setenv(char *str, t_env *env)
{
	char	**tmp;
	char	**old_env;
	int		z;

	z = 0;
	if (is_key(str, env))
	{
		z = replace_var(str, env);
		return (z);
	}
	old_env = env->env_g;
	tmp = create_new_env(env);
	if (!tmp)
		return (0);
	while (tmp[z])
		z++;
	tmp[z] = ft_strdup(str);
	tmp[z + 1] = NULL;
	if (!tmp[z])
		return (free_lst(tmp), errno);
	free_lst(old_env);
	env->env_g = tmp;
	return (0);
}
