/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:21:07 by mbartsch          #+#    #+#             */
/*   Updated: 2023/06/28 18:48:03 by mbartsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MS_PARSER_H
# define MS_PARSER_H

# ifndef T_TOKEN
#  define T_TOKEN

typedef struct s_token{
	char			*data;
	int				type;
	struct s_token	*next;
}				t_token;

# endif

# ifndef T_LLTOKEN
#  define T_LLTOKEN

typedef struct s_lltoken
{
	t_token	*lltoken;
	int		ntokens;
}				t_lltoken;

# endif

typedef struct s_loc{
	int	start;
	int	end;
}	t_loc;

typedef struct s_expansion{
	int					type;
	char				*parameter;
	struct s_loc		*loc;
	struct s_expansion	*next;
}	t_expansion;

typedef struct s_name{
	char				*text;
	int					type;
	struct s_expansion	*expansion;
}	t_name;

typedef struct s_op{
	char	*text;
	int		type;
}	t_op;

typedef struct s_file{
	char				*text;
	int					type;
	struct s_expansion	*expansion;
}	t_file;

typedef struct s_prefix{
	char				*text;
	int					type;
	struct s_expansion	*expansion;
	struct s_op			*op;
	struct s_file		*file;
	struct s_prefix		*next;
}	t_prefix;

typedef struct s_suffix{
	char				*text;
	int					type;
	struct s_expansion	*expansion;
	struct s_op			*op;
	struct s_file		*file;
	struct s_suffix		*next;
}	t_suffix;

typedef struct s_command{
	int					type;
	struct s_name		*name;
	struct s_prefix		*prefix;
	struct s_suffix		*suffix;
}	t_command;

typedef struct s_logical{
	int				type;
	int				op;
	struct s_liste	*left;
	struct s_liste	*right;
}	t_logical;

typedef struct s_subshell{
	int				type;
	struct s_liste	*liste;
}	t_subshell;

typedef struct s_pipe{
	int				type;
	struct s_liste	*liste;
}	t_pipe;

typedef struct s_start{
	struct s_command	*command;
	struct s_subshell	*subshell;
	struct s_pipe		*pipeline;
	struct s_logical	*logicalexpression;
}	t_start;

typedef struct s_liste{
	struct s_start	*start;
	int				type;
	struct s_liste	*next;
}	t_liste;

typedef struct s_root{
	int				type;
	struct s_liste	*liste;
}	t_root;

// utility functions
int			ntt(t_token **token);
int			ctt(t_token **token);
int			is_redirect(int type);
int			is_word(int type);
int			is_pipe(t_token **token);
int			is_command(t_token **token);
int			is_logical(t_token **token);
int			is_sub(t_token **token);
int			is_sub_cl(t_token **token);
int			is_op(t_token **token);
int			check_syntax(t_token **token);
int			ms_data_copy(char **dest, char *src);
int			next_token(t_token **token);
int			is_expandable(t_token **token);
int			has_expansion(char *str);
int			is_expansion(char check);
int			is_suffix(int type);

// initilising functions
t_file		*init_file(void);
t_subshell	*init_subshell(void);
t_root		*init_root(void);
t_command	*init_command(void);
t_name		*init_name(void);
t_prefix	*init_prefix(void);
t_suffix	*init_suffix(void);
t_op		*init_op(void);
t_expansion	*init_expansion(void);
t_loc		*init_loc(void);
t_logical	*init_logical(void);
t_liste		*init_liste(void);
t_start		*init_start(void);
t_pipe		*init_pipe(void);
int			parser_main(t_lltoken *lst, t_root **ast);

//node builds
t_command	*command_node(t_token **token, t_prefix *pre);
t_command	*empty_command_node(t_prefix *pre);
t_suffix	*suffix_node(t_token **token);
t_prefix	*prefix_node(t_token **token);
t_op		*op_node(t_token **token);
t_file		*file_node(t_token **token);
t_loc		*loc_node(int start, int end);
t_name		*name_node(t_token **token);
t_expansion	*expansion_node(char *str, int start);
t_root		*root_node(void);
t_liste		*liste_node(void);
t_liste		*build_command(t_token **token, t_liste *first);
t_liste		*build_pipe(t_token **token, t_liste *first);
t_liste		*build_logical(t_token **token, t_liste *first, int is_subshell);
t_liste		*build_subshell(t_token **token, t_liste *first);
t_liste		*run_tokens(t_token **token);
t_liste		*run_tokens_subshell(t_token **token);
t_liste		*run_tokens_subshell_logical(t_token **token);
t_liste		*run_tokens_logical(t_token **token);

//error handling
void		*syntax_error_token(t_token **token, t_liste *first);
void		*error_ambigous_redirect(t_token **token);
void		*error_bracket_close(t_liste *tmp);
void		*free_command(t_command *tmp);
void		*free_name(t_name *tmp);
void		*free_expansion(t_expansion *tmp);
void		*free_prefix(t_prefix *tmp);
void		*free_suffix(t_suffix *tmp);
void		*free_loc(t_loc *tmp);
void		*free_op(t_op *tmp);
void		*free_file(t_file *tmp);
void		*free_subshell(t_subshell *tmp);
void		*free_pipe(t_pipe *tmp);
void		*free_logical(t_logical *tmp);
void		*free_liste(t_liste *tmp);
void		*free_start(t_start *tmp);
void		*free_root(t_root *tmp);
void		*free_old(t_liste *tmp);

// copy functions
t_loc		*cp_loc(t_loc *cp);
t_expansion	*cp_expansion(t_expansion *cp);
t_name		*cp_name(t_name *cp);
t_op		*cp_op(t_op *cp);
t_file		*cp_file(t_file *cp);
t_prefix	*cp_prefix(t_prefix *cp);
t_suffix	*cp_suffix(t_suffix *cp);
t_command	*cp_command(t_command *cp);
t_logical	*cp_logical(t_logical *cp);
t_subshell	*cp_subshell(t_subshell *cp);
t_pipe		*cp_pipe(t_pipe *cp);
t_start		*cp_start(t_start *cp);
t_liste		*cp_liste(t_liste *cp);
t_root		*cp_root(t_root *cp);

//print ast
void		print_root(t_root *tmp, int in);
#endif
