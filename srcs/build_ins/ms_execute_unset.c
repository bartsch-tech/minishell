/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:54:08 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**new_env(t_env *env)
{
	int		z;
	char	**tmp;

	z = 0;
	while (env->env_g && env->env_g[z])
		z++;
	tmp = (char **)malloc(sizeof(char *) * z);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	**create_new_env(char *str, t_env *env)
{
	char	**tmp;
	char	*key;
	int		z;
	int		z2;

	z = 0;
	z2 = 0;
	tmp = new_env(env);
	if (!tmp)
		return (NULL);
	while (env->env_g && env->env_g[z2])
	{
		key = get_key(env->env_g[z2]);
		if (ft_memcmp(str, key, ft_strlen(key)))
		{
			tmp[z] = ft_strdup(env->env_g[z2]);
			if (!tmp[z])
				return (free(key), free_lst(tmp));
			z++;
		}
		z2++;
		free(key);
	}
	tmp[z] = NULL;
	return (tmp);
}

static int	handle_unset(t_command *tmp, t_env *env)
{
	t_suffix	*ptr;
	char		**new_env;
	char		**old_env;

	if (!tmp->suffix)
		return (1);
	ptr = tmp->suffix;
	old_env = env->env_g;
	while (ptr)
	{
		if (is_key(ptr->text, env))
		{
			new_env = create_new_env(ptr->text, env);
			if (!new_env)
				return (errno);
			free_lst(old_env);
			env->env_g = new_env;
		}
		ptr = ptr->next;
	}
	return (0);
}

int	execute_unset(t_command *tmp, int in, int out, t_env *env)
{
	int	ret;

	ret = 0;
	if (tmp->prefix)
		ret = execute_prefix(tmp->prefix, &in, &out, env);
	if (ret != 0)
		return (ret);
	if (tmp->suffix)
		ret = execute_suffix(tmp->suffix, &in, &out);
	if (ret != 0)
		return (ret);
	ret = dup_io(in, out);
	if (ret != 0)
		return (ret);
	ret = handle_unset(tmp, env);
	return (ret);
}
