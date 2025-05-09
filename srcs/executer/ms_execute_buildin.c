/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:53 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:00 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	safe_io(int *safe_in, int *safe_out)
{
	*safe_in = dup(STDIN_FILENO);
	if (*safe_in == -1)
		return (perror("ms: dup error"), errno);
	*safe_out = dup(STDOUT_FILENO);
	if (*safe_out == -1)
		return (perror("ms: dup error"), errno);
	return (0);
}

int	handle_buildin(t_command *tmp, int in, int out, t_env *env)
{
	int	safe_in;
	int	safe_out;
	int	ret;

	ret = safe_io(&safe_in, &safe_out);
	if (ret != 0)
		return (ret);
	if (check_buildin(tmp->name->text) == 1)
		ret = execute_echo(tmp, in, out, env);
	else if (check_buildin(tmp->name->text) == 3)
		ret = execute_pwd(tmp, in, out, env);
	else if (check_buildin(tmp->name->text) == 2)
		ret = execute_cd(tmp, in, out, env);
	else if (check_buildin(tmp->name->text) == 4)
		ret = execute_export(tmp, in, out, env);
	else if (check_buildin(tmp->name->text) == 5)
		ret = execute_unset(tmp, in, out, env);
	else if (check_buildin(tmp->name->text) == 6)
		ret = execute_env(tmp, in, out, env);
	else
		ret = execute_exit(tmp, in, out, env);
	if (ret != 0)
		return (ret);
	ret = dup_io(safe_in, safe_out);
	return (ret);
}
