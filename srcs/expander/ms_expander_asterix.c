/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_asterix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:20:46 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:39:46 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fnmatch(const char *pattern, char *dir)
{
	if (!*pattern)
		return (*dir == '\0');
	if (*pattern == '*')
	{
		if (ft_fnmatch(pattern + 1, dir))
			return (1);
		if (*dir && ft_fnmatch(pattern, dir + 1))
			return (1);
		return (0);
	}
	if (!*dir)
		return (0);
	if (*pattern == *dir)
		return (ft_fnmatch(pattern + 1, dir + 1));
	return (0);
}

static void	*append_return(t_suffix *first, const char *pattern, char *name)
{
	t_suffix	*new;

	if (check_dir(name))
		return (first);
	if (ft_memcmp(first->text, pattern, ft_strlen(pattern)) == 0)
	{
		free(first->text);
		first->type = P_WORD;
		first->text = ft_strdup(name);
		if (!first->text)
			return (free_suffix(first));
		return (first);
	}
	new = init_suffix();
	if (!new)
		return (free_suffix(first));
	new->type = P_WORD;
	new->text = ft_strdup(name);
	if (!new->text)
		return (free_suffix(new), free_suffix(first));
	append_suffix(first, new);
	return (first);
}
/*
static void	*append_return(t_suffix *first, const char *pattern, char *name)
{
	t_suffix	*tmp;

	tmp = NULL;
	if ((ft_memcmp(first->text, pattern, ft_strlen(pattern)) == 0) && \
		(ft_memcmp(first->text, pattern, ft_strlen(first->text)) == 0))
	{
		free(first->text);
		first->text = ft_strdup(name);
		if (!first->text)
			return (free_suffix(first));
		first->type = P_WORD;
	}
	else
	{
		tmp = init_suffix();
		if (!tmp)
			return (free_suffix(first));
		tmp->type = P_WORD;
		tmp->text = ft_strdup(name);
		if (!tmp->text)
			return (free_suffix(tmp), free_suffix(first));
		tmp->next = first->next;
		first->next = tmp;
	}
	return (first);
}*/

static t_suffix	*globber(t_suffix *first, const char *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*dir;
	char			tmp[MAX_DIR_LEN];
	t_suffix		*ret;

	ret = NULL;
	if (!getcwd(tmp, sizeof(tmp)))
		return (NULL);
	dir_ptr = opendir(tmp);
	if (!dir_ptr)
		return (NULL);
	dir = readdir(dir_ptr);
	while (dir)
	{
		if (ft_fnmatch(pattern, dir->d_name))
			if (!append_return(first, pattern, dir->d_name))
				return (free_suffix(ret));
		dir = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (ret);
}

static void	free_suffix_ones(t_suffix *tmp)
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
		if (tmp->op)
			tmp->op = free_op(tmp->op);
		if (tmp->file)
			tmp->file = free_file(tmp->file);
		free(tmp);
		tmp = NULL;
	}
}

int	exp_asterix(t_suffix *tmp)
{
	t_suffix	*store_follow;
	t_suffix	*expanded;
	t_suffix	*ptr;
	char		*pattern;

	pattern = ft_strdup(tmp->text);
	if (!pattern)
		return (errno);
	store_follow = tmp->next;
	expanded = globber(tmp, pattern);
	if (!expanded)
		return (free(pattern), errno);
	else
	{
		free_suffix_ones(tmp);
		tmp = expanded;
		ptr = tmp;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = store_follow;
		free(pattern);
		return (0);
	}
}
