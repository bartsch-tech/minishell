/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:02:20 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:11 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	char	*ret;
	int		z;
	int		z2;

	z = 0;
	z2 = 0;
	if (!str || !*str)
		return (NULL);
	while (str && str[z] && str[z] != '=')
		z++;
	ret = (char *)malloc(sizeof(char) * (z + 1));
	if (!ret)
		return (NULL);
	while (z2 < z)
	{
		ret[z2] = str[z2];
		z2++;
	}
	ret[z2] = '\0';
	return (ret);
}

int	is_key(char *key, t_env *env)
{
	char	**ptr;
	char	*key_env;

	ptr = env->env_g;
	if (!key)
		return (0);
	while (ptr)
	{
		key_env = get_key(*ptr);
		if (!key_env)
			return (0);
		if (ft_memcmp(key_env, key, ft_strlen(key_env)) == 0)
		{
			free(key_env);
			return (1);
		}
		free(key_env);
		ptr++;
	}
	return (0);
}

int	has_value(char *key)
{
	int		z;

	z = 0;
	while (key && key[z] && key[z] != '=')
		z++;
	if (key[z] == '=')
		return (1);
	return (0);
}
