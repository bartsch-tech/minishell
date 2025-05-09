/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:08:07 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/13 22:33:48 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_EXECUTER_H
# define MS_EXECUTER_H

# include "minishell.h"

typedef struct s_pipedata{
	int	pids[100];
	int	pipes[200];
	int	childs;
	int	child;
	int	fd_in;
	int	fd_out;
}	t_pipedata;

void	print_error(char *s1, char *s2, char *s3);
void	*free_lst(char **lst);
void	close_pipes(int in, int out);
int		execute_liste(t_liste *tmp, int in, int out, t_env *env);
int		liste_type(t_liste *tmp);
char	*create_command(char *text, t_env *env);
char	**fill_lst(t_suffix *tmp, char **lst);
int		handle_buildin(t_command *tmp, int in, int out, t_env *env);
int		dup_io(int fd_in, int fd_out);
int		exec_call(t_command *tmp);
int		check_buildin(char *tmp);
int		execute_redirect(t_op **op, t_file **file, int *fd_in, int *fd_out);
int		execute_assign(char *tmp);
int		execute_command(t_command *tmp, int fd_in, int fd_out, t_env *env);
int		execute_command_pipe(t_command *tmp, int fd_in, int fd_out, t_env *env);
int		execute_subshell(t_subshell *tmp, int fd_in, int fd_out, t_env *env);
int		execute_subshell_pipe(t_subshell *tmp, int fd_in, int fd_out, \
		t_env *env);
int		execute_pipe(t_pipe *tmp, int fd_in, int fd_out, t_env *env);
int		execute_logical(t_logical *tmp, int fd_in, int fd_out, t_env *env);
int		execute_prefix(t_prefix *tmp, int *fd_in, int *fd_out, t_env *env);
int		execute_suffix(t_suffix *tmp, int *fd_in, int *fd_out);
int		executer_main(t_root *tmp, t_env *env);
#endif
