/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_build_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:52:46 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/13 22:09:38 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * @brief frees a file node
*/
void	*free_file(t_file *tmp)
{
	if (tmp)
	{
		if (tmp->text)
		{
			free(tmp->text);
			tmp->text = NULL;
		}
		if (tmp->expansion)
			tmp->expansion = free_expansion(tmp->expansion);
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

static int	is_not_used(char *value)
{
	char	*check;

	check = getenv(&value[1]);
	if (!check)
		return (1);
	else
		return (0);
}

/**
 * @brief checks if the token is a valid token
*/
static int	check_valid(t_token **token)
{
	if (!is_word(ntt(token)))
	{
		syntax_error_token(token, NULL);
		return (0);
	}
	if (ntt(token) == T_AWORD)
	{
		error_ambigous_redirect(&(*token)->next);
		return (0);
	}
	else if (ntt(token) == T_DWORD && is_not_used((*token)->next->data))
	{
		error_ambigous_redirect(&(*token)->next);
		return (0);
	}
	else if (ntt(token) == T_DWORD && !is_not_used((*token)->next->data))
		return (1);
	return (2);
}

/**
 * @file ms_parser_build_file.c
 * @brief Builds a new file node. 
*/
t_file	*file_node(t_token **token)
{
	t_file	*tmp;

	tmp = init_file();
	if (!tmp)
		return (NULL);
	if (check_valid(token))
	{
		tmp->type = P_WORD;
		tmp->text = ft_strdup((*token)->next->data);
		if (check_valid(token) == 1)
		{
			tmp->expansion = expansion_node((*token)->next->data, 0);
			if (!tmp->expansion)
				return (free_file(tmp));
		}
		next_token(token);
	}
	else
		return (free_file(tmp));
	return (tmp);
}
