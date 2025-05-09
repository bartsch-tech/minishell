/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:57:44 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/28 21:41:31 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_DEFINES_H
# define MS_DEFINES_H

/**
 * token types
*/
typedef enum token_types
{
	T_NULL,
	T_AND,
	T_OR,
	T_PIPE,
	T_NWORD,
	T_DWORD,
	T_AWORD,
	T_RE_OUT,
	T_RE_IN,
	T_AP_OUT,
	T_ASSIGN,
	T_BR_OP,
	T_BR_CL,
	T_LIMITER,
}	t_ttype;

//defines for lexer

typedef enum e_parser_types
{
	P_ERROR,
	P_ROOT,
	P_LISTE,
	P_LOGICALEXPRESSION,
	P_PIPELINE,
	P_SUBSHELL,
	P_COMMAND,
	P_REDIRECT,
	P_PARAMETEREXPANSION,
	P_ASSIGNMENT,
	P_GREAT,
	P_LESS,
	P_DGREAT,
	P_WORD,
	P_XWORD,
	P_AND,
	P_OR,
}	t_ptype;
// defines for executer

# define BI_ECHO "echo\0"
# define BI_CD "cd\0"
# define BI_PWD "pwd\0"
# define BI_EXPORT "export\0"
# define BI_UNSET "unset\0"
# define BI_ENV "env\0"
# define BI_EXIT "exit\0"

# ifndef MAX_DIR_LEN
#  define MAX_DIR_LEN 256
# endif

#endif
