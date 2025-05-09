/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:49:49 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:42:14 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_sigint(int sig)
{
	(void)sig;
	write(2, "/n", 1);
	rl_redisplay();
}

void	signal_handler_sigquit(int sig)
{
	(void)sig;
	write(2, "Quit: (core dumped)\n", 7);
}

int	event_handler_child(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = signal_handler_sigquit;
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		return (perror("ms: signalhandler:"), errno);
	sig.sa_handler = signal_handler_sigint;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (perror("ms: signalhandler:"), errno);
	return (0);
}
