/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:51:04 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:06 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	text_nodes(t_command *tmp)
{
	int			z;
	t_suffix	*ptr;

	z = 0;
	ptr = tmp->suffix;
	while (ptr)
	{
		if (ptr->text)
			z++;
		ptr = ptr->next;
	}
	if (tmp->name->text)
		z++;
	return (z);
}

static char	**create_lst(t_command *tmp, t_env *env)
{
	char		**lst;
	int			anzahl;

	anzahl = text_nodes(tmp) + 1;
	lst = (char **)malloc(sizeof(char *) * anzahl);
	if (!lst)
		return (NULL);
	lst[0] = create_command(tmp->name->text, env);
	if (!*lst)
		return (free_lst(lst), NULL);
	lst = fill_lst(tmp->suffix, lst);
	if (!lst)
		return (free_lst(lst));
	return (lst);
}

void	close_pipes(int fd_in, int fd_out)
{
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
}

static int	handle_command(t_command *tmp, int fd_in, int fd_out, t_env *env)
{
	int		ret;
	char	**lst;

	ret = 0;
	if (tmp->prefix)
		ret = execute_prefix(tmp->prefix, &fd_in, &fd_out, env);
	if (ret != 0)
		return (ret);
	if (tmp->suffix)
		ret = execute_suffix(tmp->suffix, &fd_in, &fd_out);
	if (ret != 0)
		return (ret);
	ret = dup_io(fd_in, fd_out);
	if (ret != 0)
		return (ret);
	lst = create_lst(tmp, env);
	if (!lst)
		return (print_error(tmp->name->text, ": command not found", NULL), \
		exit(127), 127);
	if (lst && lst[0])
		execve(lst[0], lst, env->env_g);
	free_lst(lst);
	free_command(tmp);
	exit(errno);
}

int	execute_command(t_command *tmp, int fd_in, int fd_out, t_env *env)
{
	int		ret;
	pid_t	pid;

	ret = check_buildin(tmp->name->text);
	if (ret != 0)
		return (handle_buildin(tmp, fd_in, fd_out, env));
	pid = fork();
	if (pid == -1)
		return (perror("ms: fork"), errno);
	else if (pid == 0)
	{
		signal(SIGINT, signal_handler_sigint);
		signal(SIGQUIT, signal_handler_sigquit);
		handle_command(tmp, fd_in, fd_out, env);
	}
	else
	{
		close_pipes(fd_in, fd_out);
		pid = waitpid(-1, &ret, 0);
		if (pid == -1)
			return (errno);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
	}
	return (ret);
}
