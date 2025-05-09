/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:44:26 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:42:05 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_main(char **input, t_env *env)
{
	char	*prompt;

	prompt = create_prompt(env);
	if (!prompt)
		return (perror("ms: prompt:"), 1);
	*input = readline(prompt);
	free(prompt);
	if (!*input)
	{
		free_lst(env->env_g);
		free(env);
		exit(0);
	}
	else if (!**input)
		return (1);
	else
		return (0);
}
