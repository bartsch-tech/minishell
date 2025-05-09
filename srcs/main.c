/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:56:07 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:42:23 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_up(t_env **env, char **envp)
{
	int	ret;

	ret = 0;
	ret = build_env(env, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ret != 0)
		return (print_error(NULL, "env", strerror(errno)), ret);
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env		*env;
	t_lltoken	token_list;
	char		*input_line;
	int			ret;

	if (argc != 1 && argv != NULL)
		return (0);
	env = NULL;
	ret = start_up(&env, envp);
	if (ret != 0)
		exit(ret);
	while (1)
	{
		ret = readline_main(&input_line, env);
		if (ret == 0)
			ret = lexer_main(input_line, &token_list);
		if (ret == 0)
			ret = parser_main(&token_list, &env->ast);
		if (ret == 0)
			ret = expander_main(env->ast, env);
		if (ret == 0)
			ret = executer_main(env->ast, env);
	}
}
