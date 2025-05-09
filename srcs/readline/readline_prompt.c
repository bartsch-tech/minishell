/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <mbartsch@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:59:21 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/12 16:59:24 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_user(char *prompt, t_env *env)
{
	char	*tmp;
	char	*ret;

	tmp = ms_getenv("USER", env);
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(prompt, tmp);
	free(prompt);
	free(tmp);
	return (ret);
}

char	*create_prompt(t_env *env)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strdup("ms@\0");
	if (!prompt)
		return (NULL);
	prompt = append_user(prompt, env);
	if (!prompt)
	{
		prompt = "USER";
		tmp = ft_strjoin(prompt, ">\0");
	}
	else
	{
		tmp = ft_strjoin(prompt, ">\0");
		free(prompt);
	}
	return (tmp);
}
