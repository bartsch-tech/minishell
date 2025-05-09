/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build_ins.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:07:44 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/28 21:23:38 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_BUILD_INS_H
# define MS_BUILD_INS_H

# include "minishell.h"

int	execute_cd(t_command *tmp, int in, int out, t_env *env);
int	execute_pwd(t_command *tmp, int in, int out, t_env *env);
int	execute_echo(t_command *tmp, int in, int out, t_env *env);
int	execute_export(t_command *tmp, int in, int out, t_env *env);
int	execute_unset(t_command *tmp, int in, int out, t_env *env);
int	execute_env(t_command *tmp, int in, int out, t_env *env);
int	execute_exit(t_command *tmp, int in, int out, t_env *env);

#endif
