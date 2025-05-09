/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:21:10 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:40:03 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_len(char *eins, char *zwei, int raus)
{
	int	len;

	len = 0;
	len += ft_strlen(eins);
	len += ft_strlen(zwei);
	len -= raus;
	if (len <= 0)
		len = 1;
	return (len);
}

int	exp_insert(char **target, char *insert, int start, int end)
{
	char	*new;
	int		new_len;

	if (!insert)
	{
		insert = (char *)malloc(sizeof(char));
		if (!insert)
			return (-1);
		insert[0] = '\0';
	}
	new_len = get_new_len(*target, insert, (end - start + 1));
	new = (char *)ft_calloc(sizeof(char), new_len + 1);
	if (!new)
		return (-1);
	ft_memmove((void *)new, (void *)(*target), start);
	ft_memmove((void *)&new[start], (void *)insert, \
	ft_strlen(insert));
	ft_memmove((void *)&new[start + ft_strlen(insert)], \
	(void *)&(*target)[end + 1], ft_strlen((*target)) - (end + 1));
	*target = new;
	return (ft_strlen(insert) - (end - start) - 1);
}

int	exp_type(int type)
{
	if (type == P_XWORD)
		return (1);
	else if (type == P_ASSIGNMENT)
		return (1);
	else if (type == P_REDIRECT)
		return (1);
	return (0);
}

int	has_asterix(char *str)
{
	char	*ptr;

	ptr = str;
	while (ptr && *ptr)
	{
		if (*ptr == '*')
			return (1);
		ptr++;
	}
	return (0);
}

int	check_dir(char *dir)
{
	if (dir && *dir && *dir == '.')
		return (1);
	return (0);
}
