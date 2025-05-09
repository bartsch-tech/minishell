/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_subshell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:29 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:27 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_subshell_pipe(t_subshell *tmp, int fd_in, int fd_out, t_env *env)
{
	int		ret;

	ret = 0;
	ret = execute_liste(tmp->liste, fd_in, fd_out, env);
	free_subshell(tmp);
	exit(ret);
}

int	execute_subshell(t_subshell *tmp, int fd_in, int fd_out, t_env *env)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (pid == -1)
		return (perror("ms: fork"), errno);
	if (pid == 0)
	{
		ret = execute_liste(tmp->liste, fd_in, fd_out, env);
		free_subshell(tmp);
		exit(ret);
	}
	pid = waitpid(-1, &ret, 0);
	if (pid == -1)
		return (errno);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}
