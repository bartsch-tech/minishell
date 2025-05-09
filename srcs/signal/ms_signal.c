/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:49:49 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 15:03:29 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	event_handler_parent(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		return (perror("ms: signalhandler:"), errno);
	sig.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (perror("ms: signalhandler:"), errno);
	return (130);
}

void	event_handler(int pid, t_env *env)
{
	int		ret;
	char	*ret_str;
	char	*tmp;

	ret = 0;
	if (pid == 0)
		ret = event_handler_child();
	else
		ret = event_handler_parent();
	ret_str = ft_itoa(ret);
	if (!ret_str)
		ms_setenv("?=1", env);
	tmp = ft_strjoin("?=\0", ret_str);
	free(ret_str);
	if (!tmp)
		ms_setenv("?=1", env);
	ms_setenv(tmp, env);
	free(tmp);
}
