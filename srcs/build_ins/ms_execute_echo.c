/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:52:50 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:15:47 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_n(t_command *tmp)
{
	t_suffix	*ptr;
	int			i;

	if (!tmp->suffix)
		return (0);
	ptr = tmp->suffix;
	if (ptr->text && ft_strlen(ptr->text) == 0)
		return (0);
	if (ptr->text && ptr->text[0] == '-')
	{
		i = 1;
		while (ptr->text[i] && ptr->text[i] == 'n')
			i++;
		if (!ptr->text[i])
		{
			free(ptr->text);
			ptr->text = NULL;
			return (1);
		}
	}
	return (0);
}

static int	print_suffix(t_suffix *tmp)
{
	int	ret;

	ret = 0;
	while (tmp)
	{
		if (tmp->text)
		{
			if (printf("%s", tmp->text) < 0)
				return (1);
			if (tmp->next)
				if (printf(" ") < 0)
					return (1);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	execute_echo(t_command *tmp, int in, int out, t_env *env)
{
	int		n;
	int		ret;

	n = check_for_n(tmp);
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
	ret = print_suffix(tmp->suffix);
	if (!n)
		printf("\n");
	return (ret);
}
