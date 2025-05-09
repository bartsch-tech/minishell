/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:21:35 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 13:22:19 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_EXPANDER_H
# define MS_EXPANDER_H

# include "minishell.h"

int		expander_main(t_root *ast, t_env *env);
int		exp_liste(t_liste *tmp, t_env *env);
int		exp_prefix(t_prefix *tmp, t_env *env);
int		exp_suffix(t_suffix *tmp, t_env *env);
int		exp_name(t_command *tmp, t_env *env);
int		exp_insert(char **target, char *insert, int start, int end);
int		exp_type(int type);
int		exp_file(t_file *file, t_env *env);
int		has_asterix(char *str);
int		exp_asterix(t_suffix *tmp);
int		check_dir(char *str);
void	append_suffix(t_suffix *old, t_suffix *new);
#endif
