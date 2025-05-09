/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:37 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 15:09:46 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_buildin(char *name)
{
	if (name && !*name)
		return (0);
	if (ft_memcmp(name, BI_ECHO, 5) == 0)
		return (1);
	if (ft_memcmp(name, BI_CD, 3) == 0)
		return (2);
	if (ft_memcmp(name, BI_PWD, 4) == 0)
		return (3);
	if (ft_memcmp(name, BI_EXPORT, 7) == 0)
		return (4);
	if (ft_memcmp(name, BI_UNSET, 6) == 0)
		return (5);
	if (ft_memcmp(name, BI_ENV, 4) == 0)
		return (6);
	if (ft_memcmp(name, BI_EXIT, 5) == 0)
		return (7);
	else
		return (0);
}

static char	*check_executable(char *name)
{
	if (access(name, X_OK) == 0)
		return (name);
	else
		return (NULL);
}

static char	**env_lst(t_env *env)
{
	char	**lst;
	char	*tmp;

	tmp = ms_getenv("PATH", env);
	if (!tmp)
		return (NULL);
	lst = ft_split(tmp, ':');
	free(tmp);
	if (!lst)
		return (NULL);
	return (lst);
}

static char	*check_path(char *name, t_env *env)
{
	char	*full_path;
	char	**tmp;
	int		z;

	tmp = env_lst(env);
	z = 0;
	if (!tmp)
		return (NULL);
	while (tmp[z])
	{
		full_path = ft_strjoin(tmp[z], name);
		if (!full_path)
			return (free(name), free_lst(tmp));
		if (access(full_path, X_OK) == 0)
			return (free(name), free_lst(tmp), full_path);
		free(full_path);
		z++;
	}
	return (free(name), free_lst(tmp));
}

char	*create_command(char *tmp, t_env *env)
{
	char	*name;
	char	*full_path;

	name = ft_strdup(tmp);
	full_path = check_executable(name);
	if (full_path)
		return (full_path);
	if (tmp && tmp[0] == '.')
		return (NULL);
	full_path = ft_strjoin("/", name);
	full_path = check_path(full_path, env);
	if (full_path)
	{
		free(name);
		return (full_path);
	}
	free(name);
	if (full_path)
		free(full_path);
	return (NULL);
}
