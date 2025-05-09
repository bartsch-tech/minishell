/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:50 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:35 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @file ms_parser_error.c
 * @brief Prints error messages for syntax errors.
*/
void	*syntax_error_token(t_token **token, t_liste *first)
{
	if (*token && (*token)->next->type)
		*token = (*token)->next;
	if (first)
		free_liste(first);
	printf("ms: syntax error nead unexpected token `");
	if ((*token)->type == T_AND)
		printf("&&'");
	if ((*token)->type == T_OR)
		printf("||'");
	if ((*token)->type == T_PIPE)
		printf("|'");
	if ((*token)->type == T_BR_OP)
		printf("('");
	if ((*token)->type == T_BR_CL)
		printf(")'");
	if ((*token)->type == T_RE_OUT)
		printf(">'");
	if ((*token)->type == T_RE_IN)
		printf("<'");
	if ((*token)->type == T_AP_OUT)
		printf(">>'");
	if (is_word(ctt(token)))
		printf("%s", (*token)->data);
	printf("\n");
	return (NULL);
}

void	*error_ambigous_redirect(t_token **token)
{
	printf("ms: %s: ambigous redirect\n", (*token)->data);
	return (NULL);
}

void	*error_bracket_close(t_liste *first)
{
	printf("ms: subshell: paranthesis not closed\n");
	free_liste(first);
	return (NULL);
}
