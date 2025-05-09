/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:40 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/13 21:04:21 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the character is a valid expansion character
*/
int	is_expansion(char check)
{
	if (check >= 'A' && check <= 'Z')
		return (1);
	else if (check >= 'a' && check <= 'z')
		return (1);
	else if (check == '0' || check == '1' || check == '2' || check == '3'
		|| check == '4' || check == '5' || check == '6' || check == '7'
		|| check == '8' || check == '9')
		return (2);
	else if (check == '_' || check == '?')
		return (1);
	else
		return (0);
}

/**
 * @brief Finds the end of an expansion
 * @param str The string to parse
 * @param start The start of the expansion
 * @param end The end of the expansion (will be set by the function)
*/
static void	find_expansion(char *str, int *start, int *end)
{
	while (str[*start])
	{
		if ((str[*start] == '$' && is_expansion(str[*start + 1])))
		{
			*end = (*start) + 1;
			if (is_expansion(str[*start + 1]) == 2)
			{
				(*end)++;
				break ;
			}
			while (is_expansion(str[*end]))
				(*end)++;
			break ;
		}
		(*start)++;
	}
	if (!str[*start])
		(*end) = (*start);
}

/**
 * @brief Copies the expansion to a new string
 * @param str The string to parse
 * @param start The start of the expansion
 * @param end The end of the expansion
 * @return The new string
*/
static char	*ft_exp_cpy(char *str, int start, int end)
{
	char	*cpy;
	int		z;

	z = 0;
	start++;
	cpy = (char *)malloc(sizeof(str) * (end - start + 1));
	if (!cpy)
		return (NULL);
	while (start < end)
	{
		cpy[z] = str[start];
		z++;
		start++;
	}
	cpy[z] = '\0';
	return (cpy);
}

/**
 * @brief Frees an expansion node
*/
void	*free_expansion(t_expansion *tmp)
{
	if (tmp)
	{
		if (tmp->parameter)
		{
			free(tmp->parameter);
			tmp->parameter = NULL;
		}
		if (tmp->loc)
			tmp->loc = free_loc(tmp->loc);
		if (tmp->next)
			tmp->next = free_expansion(tmp->next);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

/**
 * @brief Creates a new expansion node
 * @param str The string to parse
 * @param start The start of the expansion
 * @return The new and initialized expansion node
*/
t_expansion	*expansion_node(char *str, int start)
{
	int			end;
	t_expansion	*tmp;

	tmp = init_expansion();
	if (!tmp)
		return (NULL);
	end = 0;
	tmp->type = P_PARAMETEREXPANSION;
	find_expansion(str, &start, &end);
	tmp->parameter = ft_exp_cpy(str, start, end);
	tmp->loc = loc_node(start, end - 1);
	if (has_expansion(&str[end]))
	{
		tmp->next = expansion_node(str, end);
		if (!tmp->next)
			return (free_expansion(tmp));
	}
	if (!tmp->parameter || !tmp->loc)
		return (free_expansion(tmp));
	return (tmp);
}
