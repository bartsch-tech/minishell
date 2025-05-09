/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:13:02 by mgraf             #+#    #+#             */
/*   Updated: 2023/07/19 14:43:06 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft-42/libft.h"
# include "ms_parser.h"
# include "ms_defines.h"
# include "ms_env.h"
# include "ms_expander.h"
# include "ms_build_ins.h"
# include "lexer.h"
# include "ms_executer.h"
# include "ms_build_ins.h"
# include "ms_signal.h"
# include <string.h>
# include <signal.h>

int		readline_main(char **input, t_env *env);
char	*create_prompt(t_env *env);

#endif
