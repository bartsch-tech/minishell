/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:34:56 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/14 14:15:08 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/// @brief Each token is saved to a node in a linked list with it's type.
# ifndef T_TOKEN
#  define T_TOKEN

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}				t_token;
# endif
/// @brief Here the head of the linked list and number of tokens is saved.
# ifndef T_LLTOKEN
#  define T_LLTOKEN

typedef struct s_lltoken
{
	t_token	*lltoken;
	int		ntokens;
}				t_lltoken;
# endif

typedef struct s_data
{
	char		*line;
	int			len;
	t_lltoken	lex_head;
}				t_data;

// lexer_new.c
void	lexer(t_lltoken *head, char *line, int len);
void	data_destroy(t_data *data);
void	data_init(t_data *data);
int		lexer_main(char *input, t_lltoken *token_list);

// here_doc.c
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	check_here_doc(t_token *token);

// lexer_helper.c
int		is_whitespace(char c);
int		is_symbol(char c);
void	remove_quotes(char *string, char quote);
t_ttype	double_symbols(char *line, int *left, int *right, t_ttype *type);
t_ttype	close_quotes(char *line, int *position, int *len, int *i);

// lexer_list.c
void	lstadd_back(t_lltoken **list, t_token *add);
void	llist_free(t_token *token);
void	print_llist(t_lltoken token_head);

// lexer_token.c
void	get_token(char *line, int *left, int *right);
t_ttype	token_type(char c);
t_ttype	classify_token_ifadword(char *line, int left, int right);
t_ttype	classify_token(char *line, int *left, int *right, int *len);
t_token	*create_node(char *line, int left, int right, t_ttype type);
int		is_whitespace(char c);
#endif
