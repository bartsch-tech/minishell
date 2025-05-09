/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:08:35 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:38:08 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_ptr(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	z;

	z = 0;
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[z] && s2[z] && s1[z] == s2[z])
		z++;
	if (!s1[z] && !s2[z])
		return (0);
	else if (!s1[z])
		return (-1);
	else if (!s2[z])
		return (1);
	else
		return (s1[z] - s2[z]);
}

int	suffix_redirect(t_suffix *tmp)
{
	t_suffix	*ptr;

	ptr = tmp;
	while (ptr)
	{
		if (ptr->type != P_REDIRECT)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void	print_key(char *str)
{
	char	*ptr;

	ptr = str;
	while (ptr && *ptr && *ptr != '=')
	{
		printf("%c", *ptr);
		ptr++;
	}
	if (*ptr == '=')
		printf("%c", *ptr);
}

void	print_value(char *str)
{
	char	*ptr;

	ptr = str;
	while (ptr && *ptr && *ptr != '=')
		ptr++;
	if (*ptr == '=')
		ptr++;
	while (ptr && *ptr)
	{
		printf("%c", *ptr);
		ptr++;
	}
}
