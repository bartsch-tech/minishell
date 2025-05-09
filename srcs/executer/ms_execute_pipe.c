/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:39:16 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:14 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_data(t_pipedata *data, t_liste *ptr, int fd_in, int fd_out)
{
	t_liste	*tmp;
	int		z;

	z = 0;
	tmp = ptr;
	data->childs = 0;
	data->child = 0;
	data->fd_in = fd_in;
	data->fd_out = fd_out;
	ft_memset(data->pids, 0, 100);
	ft_memset(data->pipes, 0, 200);
	while (tmp)
	{
		data->childs++;
		tmp = tmp->next;
	}
	while (z < data->childs - 1)
	{
		if (pipe(data->pipes + 2 * z) == -1)
			return (perror("ms: pipe"), errno);
		z++;
	}
	return (0);
}

static void	closer_pipes(t_pipedata *data, int one, int two)
{
	int	i;

	i = 0;
	while (i < (data->childs - 1) * 2)
	{
		if (i != one && i != two)
			close(data->pipes[i]);
		i++;
	}
}

static void	run_child(t_liste *tmp, t_pipedata *data, t_env *env)
{
	int	fd_in;
	int	fd_out;

	if (data->child == 0)
	{
		fd_in = data->fd_in;
		fd_out = data->pipes[1];
	}
	else if (data->child == data->childs - 1)
	{
		fd_in = data->pipes[2 * data->child - 2];
		fd_out = data->fd_out;
	}
	else
	{
		fd_in = data->pipes[2 * data->child - 2];
		fd_out = data->pipes[2 * data->child + 1];
	}
	closer_pipes(data, 2 * data->child - 2, 2 * data->child + 1);
	if (liste_type(tmp) == P_COMMAND)
		fd_in = execute_command_pipe(tmp->start->command, fd_in, fd_out, env);
	else if (liste_type(tmp) == P_SUBSHELL)
		fd_in = execute_subshell_pipe(tmp->start->subshell, fd_in, fd_out, env);
	exit(fd_in);
}

int	run_parent(t_pipedata *data)
{
	pid_t	wpid;
	int		status;
	int		ret;

	closer_pipes(data, -1, -1);
	data->child--;
	ret = 1;
	while (data->child >= 0)
	{
		wpid = waitpid(data->pids[data->child], &status, 0);
		if (wpid == data->pids[data->childs - 1])
		{
			if ((data->child == (data->childs - 1)) && WIFEXITED(status))
				ret = WEXITSTATUS(status);
		}
		data->child--;
	}
	return (ret);
}

int	execute_pipe(t_pipe *tmp, int fd_in, int fd_out, t_env *env)
{
	t_pipedata	*data;
	int			ret;
	t_liste		*ptr;

	ptr = tmp->liste;
	data = malloc(sizeof(t_pipedata));
	if (!data)
		return (perror("ms: malloc"), errno);
	ret = init_data(data, ptr, fd_in, fd_out);
	if (ret != 0)
		return (ret);
	while (ptr)
	{
		data->pids[data->child] = fork();
		if (data->pids[data->child] == -1)
			return (perror("ms: fork"), errno);
		else if (data->pids[data->child] == 0)
			run_child(ptr, data, env);
		data->child++;
		ptr = ptr->next;
	}
	ret = run_parent(data);
	free(data);
	return (ret);
}
