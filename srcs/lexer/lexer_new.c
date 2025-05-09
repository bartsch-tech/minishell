/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:24:54 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/14 13:14:47 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../libft-42/libft.h"
#include "../../include/lexer.h"
#include "../../include/ms_defines.h"

/**
 * @brief Contains the loop to identify, class and add a token
*/
void	lexer(t_lltoken *head, char *line, int len)
{
	int		left;
	int		right;
	t_ttype	type;

	left = 0;
	right = 0;
	while (left < len && line[left] != '\0')
	{
		get_token(line, &left, &right);
		type = classify_token(line, &left, &right, &len);
		lstadd_back(&head, \
					create_node(line, left, right, type));
		head->ntokens++;
	}
}

/**
 * @brief Destroys the data obeject
 */
void	data_destroy(t_data *data)
{
	free(data->line);
	data->line = NULL;
	data->len = -1;
	llist_free(data->lex_head.lltoken);
	data->lex_head.lltoken = NULL;
	data->lex_head.ntokens = -1;
}

/**
 * Initializes the data object and detects 'exit' as input
*/
void	data_init(t_data *data)
{
	if (data->line)
		add_history(data->line);
	data->len = ft_strlen(data->line);
	data->lex_head.lltoken = NULL;
}

int	lexer_main(char *input, t_lltoken *token_liste)
{
	t_data	data;
	t_token	*tmp;

	data.line = input;
	data_init(&data);
	lexer(&data.lex_head, data.line, data.len);
	tmp = data.lex_head.lltoken;
	while (tmp->next)
		tmp = tmp->next;
	tmp->type = T_NULL;
	check_here_doc(data.lex_head.lltoken);
	free(input);
	*token_liste = data.lex_head;
	return (0);
}
