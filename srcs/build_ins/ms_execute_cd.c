/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:45 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:40 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_suffix *tmp, t_env *env)
{
	char	*dir;

	if (tmp)
	{
		if (chdir(tmp->text))
			return (print_error("cd: ", tmp->text, strerror(errno)), errno);
	}
	else
	{
		dir = ms_getenv("HOME", env);
		if (chdir(dir))
		{
			free(dir);
			return (print_error("cd: ", "HOME not set", NULL), errno);
		}
		free(dir);
	}
	return (0);
}

static int	check_valid_suffix(t_suffix *tmp)
{
	t_suffix	*ptr;
	int			words;

	ptr = tmp;
	if (!ptr)
		words = 1;
	else
		words = 0;
	while (ptr)
	{
		if (ptr->type != P_REDIRECT)
			words++;
		ptr = ptr->next;
	}
	return (words);
}

int	execute_cd(t_command *tmp, int in, int out, t_env *env)
{
	int	ret;

	ret = 0;
	if (check_valid_suffix(tmp->suffix) > 1)
		return (print_error(NULL, "cd", "too many arguments"), 1);
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
	ret = ms_cd(tmp->suffix, env);
	return (ret);
}
