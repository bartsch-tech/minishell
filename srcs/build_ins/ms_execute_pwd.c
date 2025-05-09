/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:53:54 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:58 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(void)
{
	char	tmp[MAX_DIR_LEN];

	if (!getcwd(tmp, sizeof(tmp)))
		return (126);
	printf("%s\n", tmp);
	return (0);
}

int	execute_pwd(t_command *tmp, int in, int out, t_env *env)
{
	int	ret;

	ret = 0;
	if (tmp->prefix)
		ret = execute_prefix(tmp->prefix, &in, &out, env);
	if (ret != 0)
		return (ret);
	if (tmp->suffix)
		ret = execute_suffix(tmp->suffix, &in, &out);
	if (ret != 0)
		return (ret);
	ret = dup_io(in, out);
	if (ret != 0)
		return (ret);
	ret = ms_pwd();
	return (ret);
}
