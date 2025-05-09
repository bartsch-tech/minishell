/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:32:40 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/13 23:33:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Identifies tokens (one at a time)
 * @param *line which is searched
 * @param *left where the token starts
 * @param *right starts screening here and updates the value with the token end
*/
void	get_token(char *line, int *left, int *right)
{
	*left = *right;
	while (is_whitespace(line[*left]))
		*left = *left + 1;
	*right = *left;
	if (is_symbol(line[*right]) && line[*right - 1] != '\\')
		*right = *right + 1;
	else
	{
		while (!is_whitespace(line[*right]) && line[*right] != '\0')
		{
			*right = *right + 1;
			if (is_symbol(line[*right]) && line[*right - 1] != '\\')
				break ;
		}
	}
}

t_ttype	token_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	if (c == 0)
		return (T_NULL);
	if (c == '=')
		return (T_ASSIGN);
	if (c == '>')
		return (T_RE_OUT);
	if (c == '<')
		return (T_RE_IN);
	if (c == '(')
		return (T_BR_OP);
	if (c == ')')
		return (T_BR_CL);
	return (T_NULL);
}

/**
 * @brief Checking of word is contains * or $
 * ft_strchr returns null if nothing is found (!)
*/
t_ttype	classify_token_ifadword(char *line, int left, int right)
{
	if (ft_strchr(line + left, '=') <= (line + right))
		if (ft_strchr(line + left, '='))
			if (ft_strchr(line + left, '=') != line)
				return (T_ASSIGN);
	if (ft_strchr(line + left, '$') <= (line + right))
		if (ft_strchr(line + left, '$'))
			return (T_DWORD);
	if ((ft_strchr(line + left, '*')) <= (line + right))
		if (ft_strchr(line + left, '*'))
			return (T_AWORD);
	if (line[left] == '\0')
		return (T_NULL);
	return (T_NWORD);
}

/**
 * @brief Checks what kind of token it is given.
 * If token is ' or " then the closing quote is searched and *right updated.
 * Int left and right combined to int position for argument with bitshifting.
 * 1. Checking for double symbols 2. closing corresponding quotes 3. checking
 * symbol 4. checking if AWORD or DWORD, otherwise NWORD
 * @return kind of token found
*/
t_ttype	classify_token(char *line, int *left, int *right, int *len)
{
	int		i;
	int		position;
	t_ttype	type;

	i = 1;
	position = (*left << 16 | *right);
	if (double_symbols(line, left, right, &type))
		return (type);
	else if (line[*left] == '\'' && (line[*left + i] != 0))
		type = close_quotes(line, &position, len, &i);
	else if (line[*left] == '\"' && (line[*left + i] != 0))
		type = close_quotes(line, &position, len, &i);
	else if (is_symbol(line[*left]))
		return (token_type(line[*left]));
	else
		type = classify_token_ifadword(line, *left, *right);
	*left = (position >> 16) & 0xFFFF;
	*right = position & 0xFFFF;
	return (type);
}

/**
 * Creates the token node with the given information, also
 * handles removing quotes
 * @returns t_token node
*/
t_token	*create_node(char *line, int left, int right, t_ttype type)
{
	t_token	*node;
	char	*content;

	content = (char *)malloc(sizeof(char) * (right - left + 1));
	ft_strlcpy(content, line + left, right - left + 1);
	if (type == T_NWORD || type == T_DWORD || type == T_AWORD)
	{
		if (content[0] == '\'')
			remove_quotes(content, '\'');
		else if (content[0] == '\"')
			remove_quotes(content, '\"');
	}
	node = (t_token *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->data = content;
	node->type = type;
	node->next = NULL;
	return (node);
}
