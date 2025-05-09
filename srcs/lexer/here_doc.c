/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:57:49 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/14 14:55:59 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

void	here_doc_loop(char *eof, int fd)
{
	char	*here_line;

	while (1 && fd != -1)
	{
		here_line = readline("heredoc> ");
		if (ft_strcmp(here_line, eof) == 0)
		{
			free(here_line);
			break ;
		}
		write(fd, here_line, ft_strlen(here_line));
		write(fd, "\n", 1);
		free(here_line);
	}
}

void	check_here_doc(t_token *token)
{
	char	*eof;
	int		fd;

	while (token)
	{
		if (token->next && token->next->type == T_LIMITER && token->next->next)
		{
			if (token->next->next->type == T_NULL)
			{
				token->next->type = T_RE_IN;
				return ;
			}
			eof = ft_strdup(token->next->next->data);
			fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
			here_doc_loop(eof, fd);
			close(fd);
			free(eof);
			token->next->type = T_RE_IN;
			free(token->next->next->data);
			token->next->next->data = ft_strdup("heredoc.txt");
		}
		token = token->next ;
	}
}
