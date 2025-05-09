/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:26:28 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/13 23:30:42 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * whitespaces = " \\t\\r\\n\\v"
*/
int	is_whitespace(char c)
{
	if (c == 32 || c == '\t' || c == '\r' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

/**
 * symbols = "<|>&()" && "'""
*/
int	is_symbol(char c)
{
	if (c == '<' || c == '|' || c == '>' || c == '(' || c == ')')
		return (1);
	else if (c == '\'' || c == '\"' || c == '&')
		return (1);
	return (0);
}

/**
 * Removes starting and ending quotes \" and \' by shifting string -1 and \0
*/
void	remove_quotes(char *string, char quote)
{
	int	i;

	i = 1;
	if (quote != '\'' && quote != '"')
		return ;
	if ((string[0] == quote) && string[i + 1] != '\0')
	{
		while (string[i] != quote)
		{
			string[i - 1] = string[i];
			i++;
		}
		string[i - 1] = '\0';
	}
	else if ((string[0] == quote && string [1] == quote))
		string[0] = '\0';
}

/**
 * Checks for && || >> and <<
 * @returns tokentype and updates right position
*/
t_ttype	double_symbols(char *line, int *left, int *right, t_ttype *type)
{
	if (*left == *right)
	{
		*type = (T_NULL);
		return (0);
	}
	else if (line[*left] == '>' && line[*left + 1] == '>')
		*type = (T_AP_OUT);
	else if (line[*left] == '|' && line[*left + 1] == '|')
		*type = (T_OR);
	else if (line[*left] == '&' && line[*left + 1] == '&')
		*type = (T_AND);
	else if (line[*left] == '<' && line[*left + 1] == '<')
		*type = (T_LIMITER);
	else
	{
		*type = (T_NWORD);
		return (0);
	}
	*right = *right + 1;
	return (1);
}

/**
 * @brief closes the quotes by finding the next occurence of character at [0]
 * @returns ttype and via adress positions left and right and counter i.
*/
t_ttype	close_quotes(char *line, int *position, int *len, int *i)
{
	int		left;
	int		right;
	char	c;

	left = (*position >> 16) & 0xFFFF;
	right = (*position) & 0xFFFF;
	c = line[left];
	while ((line[left + *i] != 0))
	{
		if (line[left + *i] == '\\')
			*i = *i + 2;
		if (line[left + *i] != c)
			*i = *i + 1;
		if (line[left + *i] == c)
			break ;
	}
	if (*len <= left + *i)
		printf("ERROR\n");
	right = right + *i;
	*position = left << 16 | right;
	if (c == '\"')
		if (ft_strchr(line + left, '$') <= (line + right))
			if (ft_strchr(line + left, '$'))
				return (T_DWORD);
	return (T_NWORD);
}
