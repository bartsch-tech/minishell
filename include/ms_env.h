/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:34 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/28 21:23:58 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_ENV_H
# define MS_ENV_H

# include "minishell.h"

typedef struct s_env{
	char	**env_g;
	t_root	*ast;
}	t_env;

int		build_env(t_env **tmp, char *envp[]);
int		update_env(t_env *tmp);
char	*ms_getenv(char *str, t_env *env);
char	**cp_lst(char **cp);
void	swap_ptr(char **a, char **b);
int		ft_strcmp(char *s1, char *s2);
int		suffix_redirect(t_suffix *tmp);
char	**sort_env(t_env *env);
int		ms_setenv(char *str, t_env *env);
char	*get_key(char *str);
int		is_key(char *key, t_env *env);
void	print_key(char *str);
void	print_value(char *str);
int		has_value(char *key);

#endif
