/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:55:15 by mbartsch          #+#    #+#             */
/*   Updated: 2023/09/14 14:41:47 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_liste(t_liste *liste, int in);

void	print_in(int in)
{
	while (in)
	{
		printf("\t");
		in--;
	}
}

void	print_loc(t_loc *loc, int in)
{
	print_in(in);
	printf("location\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("start: %d\n", loc->start);
	print_in(in + 1);
	printf("ende: %d\n", loc->end);
	print_in(in);
	printf("}\n");
}

void	print_expansion(t_expansion *exp, int in)
{
	print_in(in);
	printf("expansion\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("expansion type: %d\n", exp->type);
	print_in(in + 1);
	printf("expansion parameter: %s\n", exp->parameter);
	print_loc(exp->loc, in);
	print_in(in);
	printf("}\n");
	if (exp->next)
		print_expansion(exp->next, in);
}

void	print_op(t_op *op, int in)
{
	print_in(in);
	printf("operator\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("op type: %d\n", op->type);
	print_in(in + 1);
	printf("op text: %s\n", op->text);
	print_in(in);
	printf("}\n");
}

void	print_file(t_file *file, int in)
{
	print_in(in);
	printf("file\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("file type: %d\n", file->type);
	print_in(in + 1);
	printf("file text: %s\n", file->text);
	if (file->expansion)
		print_expansion(file->expansion, in);
	print_in(in);
	printf("}\n");
}

void	print_name(t_name *name, int in)
{
	print_in(in);
	printf("name\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("name type: %d\n", name->type);
	print_in(in + 1);
	printf("name text: %s\n", name->text);
	if (name->expansion)
		print_expansion(name->expansion, in);
	print_in(in);
	printf("}\n");
}

void	print_prefix(t_prefix *prefix, int in)
{
	print_in(in);
	printf("prefix\n");
	print_in(in);
	printf("{\n");
	if (prefix->type == P_REDIRECT)
	{
		print_in(in + 1);
		printf("prefix type: %d\n", prefix->type);
		print_op(prefix->op, in + 1);
		print_file(prefix->file, in + 1);
	}
	else
	{
		print_in(in + 1);
		printf("prefix type: %d\n", prefix->type);
		print_in(in + 1);
		printf("prefix text: %s\n", prefix->text);
		if (prefix->expansion)
			print_expansion(prefix->expansion, in + 1);
	}
	print_in(in);
	printf("}\n");
	if (prefix->next)
		print_prefix(prefix->next, in);
}

void	print_suffix(t_suffix *suffix, int in)
{
	print_in(in);
	printf("suffix\n");
	print_in(in);
	printf("{\n");
	if (suffix->type == P_REDIRECT)
	{
		print_in(in + 1);
		printf("suffix type: %d\n", suffix->type);
		print_op(suffix->op, in + 1);
		print_file(suffix->file, in + 1);
	}
	else
	{
		print_in(in + 1);
		printf("suffix type: %d\n", suffix->type);
		print_in(in + 1);
		printf("suffix text: %s\n", suffix->text);
		if (suffix->expansion)
			print_expansion(suffix->expansion, in + 1);
	}
	print_in(in);
	printf("}\n");
	if (suffix->next)
		print_suffix(suffix->next, in);
}

void	print_command(t_command *command, int in)
{
	print_in(in);
	printf("command\n");
	print_in(in);
	printf("{\n");
	if (command->prefix)
		print_prefix(command->prefix, in + 1);
	print_name(command->name, in + 1);
	if (command->suffix)
		print_suffix(command->suffix, in + 1);
	print_in(in);
	printf("}\n");
}

void	print_logical(t_logical *logical, int in)
{
	print_in(in);
	printf("logical\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("logical type: %d\n", logical->type);
	print_in(in + 1);
	printf("logical op: %d\n", logical->op);
	print_in(in + 1);
	printf("logical left:\n");
	print_in(in + 1);
	printf("{\n");
	print_in(in + 2);
	printf("liste:\n");
	print_in(in + 2);
	printf("{\n");
	print_liste(logical->left, in + 2);
	print_in(in + 2);
	printf("}\n");
	print_in(in + 1);
	printf("}\n");
	print_in(in + 1);
	printf("logical right:\n");
	print_in(in + 1);
	printf("{\n");
	print_in(in + 2);
	printf("liste:\n{\n");
	print_liste(logical->right, in + 2);
	print_in(in + 2);
	printf("}\n");
	print_in(in + 1);
	printf("}\n");
	print_in(in);
	printf("}\n");
}

void	print_subshell(t_subshell *subshell, int in)
{
	print_in(in);
	printf("subshell\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("subshell type: %d\n", subshell->type);
	print_in(in + 1);
	printf("liste:\n");
	print_in(in + 1);
	printf("{\n");
	print_liste(subshell->liste, in + 1);
	print_in(in + 1);
	printf("}\n");
	print_in(in);
	printf("}\n");
}

void	print_pipe(t_pipe *pipe, int in)
{
	print_in(in);
	printf("pipeline\n");
	print_in(in);
	printf("{\n");
	print_in(in + 1);
	printf("pipeline type: %d\n", pipe->type);
	print_in(in + 1);
	printf("liste:\n");
	print_in(in + 1);
	printf("{\n");
	print_liste(pipe->liste, in + 1);
	print_in(in + 1);
	printf("}\n");
	print_in(in);
	printf("}\n");
}

void	print_start(t_start *start, int in)
{
	if (start->command)
		print_command(start->command, in);
	else if (start->logicalexpression)
		print_logical(start->logicalexpression, in);
	else if (start->pipeline)
		print_pipe(start->pipeline, in);
	else if (start->subshell)
		print_subshell(start->subshell, in);
}

void	print_liste(t_liste *liste, int in)
{
	if (liste)
	{
		print_start(liste->start, in);
		if (liste->next)
			print_liste(liste->next, in);
	}
}

void	print_root(t_root *root, int in)
{
	if (root)
	{
		print_in(in);
		printf("root\n");
		print_in(in);
		printf("{\n");
		print_liste(root->liste, in);
		print_in(in);
		printf("}\n");
	}
}*/
