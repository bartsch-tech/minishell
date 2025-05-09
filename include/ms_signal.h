/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:28:15 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/30 16:10:36 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

void	event_handler(int pid, t_env *env);
int		event_handler_child(void);
void	signal_handler(int sig);
void	signal_handler_sigint(int sig);
void	signal_handler_sigquit(int sig);
#endif
