/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:56 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:53 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key(char *str)
{
	int		z;
	char	**tmp;

	z = 0;
	tmp = ft_split(str, '=');
	if (!tmp)
		return (errno);
	if (ft_isalpha((*tmp[z])) == 0 && (*tmp)[z] != '_')
	{
		free_lst(tmp);
		return (1);
	}
	z = 1;
	while ((*tmp)[z] && ft_isalpha((*tmp)[z]) && ft_isalnum((*tmp)[z]))
		z++;
	if ((*tmp)[z] != '\0')
	{
		free_lst(tmp);
		return (1);
	}
	free_lst(tmp);
	return (0);
}

static int	print_export(t_env *env)
{
	char	**prnt;
	int		z;

	z = 0;
	prnt = sort_env(env);
	if (!prnt)
		return (1);
	while (prnt[z])
	{
		printf("declare -x ");
		print_key(prnt[z]);
		if (has_value(prnt[z]))
		{
			printf("\"");
			print_value(prnt[z]);
			printf("\"");
		}
		printf("\n");
		z++;
	}
	free_lst(prnt);
	return (0);
}

static int	append_env(t_env *env, t_suffix *tmp)
{
	int	ret;

	ret = 0;
	if (!tmp || !tmp->text)
		return (ret);
	ret = check_key(tmp->text);
	if (ret != 0)
		return (print_error("export: ", tmp->text, \
				"not a valid identifier"), ret);
	ret = ms_setenv(tmp->text, env);
	if (tmp->next)
		ret = append_env(env, tmp->next);
	return (ret);
}

static int	handle_export(t_command *tmp, t_env *env)
{
	int	ret;

	ret = 0;
	if (suffix_redirect(tmp->suffix))
		ret = print_export(env);
	else
		ret = append_env(env, tmp->suffix);
	return (ret);
}

int	execute_export(t_command *tmp, int in, int out, t_env *env)
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
	ret = handle_export(tmp, env);
	return (ret);
}
