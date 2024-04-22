/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:01:00 by yrio              #+#    #+#             */
/*   Updated: 2024/04/02 11:45:08 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdlib.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "lib_utils.h"
# include "get_next_line.h"
// colors
# define BLK "\e[0;90m"
# define RED "\e[1;31m" // ERROR
# define GR "\e[1;92m"
# define Y "\e[1;93m"
# define BLU "\e[1;94m" //Minishell name
# define PUR "\e[1;95m"
# define CY "\e[1;96m"
# define WH "\e[0;97m"
# define RST "\e[0m"
# define ERR_MAL "-- Malloc failed --\n"

# define OPERATOR_AND 1
# define OPERATOR_OR 2
# define LST_CMD 3

# define IN_CMD 1
# define IN_HEREDOC 2
# define CTRL_C 3
# define CTRL_BS 4

# define HERE_DOC 1
# define NO_HERE_DOC 2

extern int	g_status_code;

typedef struct t_list {
	int				index;
	int				display;
	char			*key;
	char			*value;
	char			**splitting;
	struct t_list	*next;
}				t_envlist;

typedef struct s_token
{
	bool			in_doquote;
	bool			in_sgquote;
	bool			error;
	int				in_pars;
	int				out_pars;
	bool			in_pars_suite;
	bool			out_pars_suite;
	int				tot_pars;
}	t_token;

typedef struct s_infopars
{
	int					spe;
	char				*str;
	struct s_infopars	*next;
	struct s_infopars	*prec;
}	t_infopars;

typedef struct s_lstcmd
{
	int				error;
	int				index;
	int				max_index;
	int				available;
	char			**cmd;
	char			**t_path;
	pid_t			child;
	int				last_infile;
	int				in_file;
	char			*in_file_name;
	int				out_file;
	struct s_lstcmd	*next;
	struct s_lstcmd	*prec;
}	t_lstcmd;

typedef struct s_tree
{
	int				type;
	struct s_tree	*parent;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
	t_lstcmd		*lst_cmd;
}	t_tree;

typedef struct s_shell
{
	int			exit_status;
	int			last_exit_status;
	char		**path;
	int			std_out;
	int			std_in;
	int			nbr_path;
	int			len_cmds;
	char		**env;
	t_envlist	*lst_envs;
	char		**str_split;
	t_tree		*tree;
	t_infopars	*lst_char;
}	t_shell;

typedef struct s_data
{
	char			*tmp;
	char			*new_str;
	int				i;
	char			*dir_path;
	char			*dir_path_tmp;
	char			*new_dir_path;
	DIR				*rep;
	struct dirent	*fichierlu;
	t_infopars		*new_lst;
	t_infopars		*tmp_box;
}	t_data;

// Erreur
void		launch_shell(int argc, const char **env);
void		gestion_exit(char *msg, t_shell *bash);
bool		check_lst_split(t_shell *bash);
bool		check_process(t_infopars *pars);
bool		in_feature(t_infopars *curr, t_shell *bash);
bool		only_space(char *str);
// Get
void		get_true_path(t_shell *bash, char const **env);
// Case
t_infopars	*diff_boxshell(char *str, int spe);
t_infopars	*cut_boxshell(char *str);
t_infopars	*first_boxshell(t_infopars *last);
t_infopars	*last_boxshell(t_infopars *curr);
// Process manipulation
t_infopars	*supp_blockshell(t_infopars *pre, t_infopars *next, \
t_infopars *curr);
// Process add
bool		build_process(char *str, t_shell *bash);
void		add_boxshell(t_infopars **all, t_infopars *part);
void		add_btw_boxshell(t_infopars *pre, t_infopars *new_lst, \
t_infopars *next, t_infopars **old);
// Free process
void		eradication(t_shell *bash, t_tree *branch);
void		free_boxshell(t_infopars **all);
void		free_shell(t_shell *bash);
void		free_blockstrshell(t_infopars *selec);
void		free_tree(t_tree *tree);
void		free_essential(t_shell *bash);
void		free_branch(t_tree *branch);
void		free_lstcmd(t_lstcmd *lst);
// Print process
void		print_strshell(t_infopars *lst);
// In
void		in_sgquote(char c, t_token *token);
void		in_doquote(char c, t_token *token);
// split minishell
int			count_minishell(char *str);
char		**split_minishell(char *str);
int			cutting(char *str, t_lstcmd *base);
// SKIP
int			skip_space(char *str);
int			skip_char(char *str);
int			skip_not_env(char *str, t_token *token);
int			name_env(char *str);
int			skip_insert_env(char *str, char c);
// ENV
char		*insert_env(char *str, t_shell *bash);
bool		replace_lstchar_env(t_infopars *lst_char, t_shell *bash);
t_infopars	*true_expand(t_infopars *curr, char **str, t_shell *bash);
bool		space_in_expand(char *str);
t_infopars	*lst_shellstr_env(char **str);
bool		take_value(char *str, t_shell *bash, t_data *x);
bool		expander(t_infopars *curr, t_shell *bash, t_infopars **new_curr);
char		*env_value(char *str, t_envlist *lst_envs, int i, t_shell *bash);
char		*insert_env_here(char *str, t_shell *bash);
bool		join_tmp(t_data *x);
int			change_(char *str, t_shell *bash, t_data *x, t_token *token);
// DOMAINE Analysis
void		listing_split(t_shell *bash);
bool		malloc_proc(t_data *tmp, char *str);
int			next_process(char *str);
bool		box_process(t_data *tmp, char *str);
bool		is_operator(char c);
bool		is_redirection(char c);
bool		box_str(t_data *tmp, char *str);
// Utils check libs_split
bool		finish_quote(char *str, t_token *token, t_shell *bash);
bool		after_operator(t_infopars *pre, t_infopars *curr, t_infopars *next, \
t_shell *bash);
bool		good_operator(char *str, t_shell *bash);
bool		good_af_pars2(t_infopars *next, t_infopars *curr, t_shell *bash);
bool		before_operator(t_infopars *curr, t_infopars *pre, t_shell *bash);
bool		check_pars(t_infopars **curr, t_token *token, t_shell *bash);
bool		check_redirection(t_infopars *curr, t_shell *bash);
void		id_shellst(t_shell *bash);
bool		sub_shell(t_infopars *lst, t_shell *bash);
// Utils lst_cmd
t_lstcmd	*build_cmd(t_infopars *lst, int index);
t_lstcmd	*create_lstcmd(t_infopars *lst, t_shell *bash, t_tree *branch);
void		print_lstcmd(t_lstcmd *lstcmd);
t_lstcmd	*first_cmd_pipe(t_lstcmd *lstcmd);
// TREE
t_tree		*build_branch(t_infopars *lstchar, t_shell *bash);
void		print_branch(t_tree *branch);
t_tree		*build_tree(t_infopars *lst_char, t_tree **main_tree);

t_infopars	*noeud_first(t_infopars *lst_char);
bool		building_tree(t_tree **curr_tree, t_infopars *last_ele, \
t_shell *bash);
t_tree		*back_parent(t_tree *curr_tree);
// void	free_tree(t_tree *main_tree);
void		print_tree(t_tree *main_tree);
void		close_tree(t_tree *curr);
//Heredoc
void		close_out_heredoc(t_shell *bash, int fd, t_lstcmd *lstcmd);
int			len_inquote(char *str);
bool		suppress_quote(t_infopars *lst_char);
t_infopars	*last_infile(t_infopars *lst_char);
void		last_outfile(t_infopars *lst_char, t_lstcmd *curr_cmd);
bool		define_last(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash, t_tree *branch);

//libft
// char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_gnl(char *s1, char *s2, size_t size);
// char		*get_next_line(int fd);
// char		*ft_strchr(const char *s, int c);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// char		**ft_split(char const *s, char c);
// int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
char		**ft_free(char **char_tab, int nb_words);
char		*ft_strdup(char *src);

//builtins
int			ft_cd(char **argv, t_shell *minishell);
int			check_args(char **args_split, t_shell *minishell);
int			ft_pwd(char **args_split);
int			ft_unset(char **args_split, t_shell *minishell);
int			ft_export(char	**args_split, t_shell *minishell);
void		no_args(t_envlist *lst_envs);
void		ft_echo(char **args_split);
void		ft_exit(char **cmd, t_shell *bash);
int			ft_env(char **args_split, t_shell *minishell);

int			check_env_key(t_shell *minishell, char *str);
char		*get_value_env(t_shell *minishell, char *key);

//lst_utils.c
t_envlist	*lst_new(char *str, int display);
void		lstadd_back(t_envlist *new, t_envlist *lst);
void		lstclear(t_envlist *lst);
t_lstcmd	*lst_index(t_lstcmd *lst, int index);
int			lst_size(t_lstcmd *lstcmd);

//builtins_utils.c
int			exec_builtins(char **cmd, t_shell *bash);
int			is_builtins(char **cmd);
void		launch_builtins(int std_out, int *fd, t_lstcmd *cmds, \
t_shell *bash);
int			check_empty_args(char **splitting_tmp);

//utils_minishell.c
void		ls_cmd(void);
char		**get_paths(char **env);
char		**free_split(char **char_tab);
void		malloc_env(t_shell *minishell, char **env);
char		**ft_split_onedel(char const *s, char c);
int			check_cmd_parsing(char *cmd);
char		*check_cmd(char *cmd, char **path_split);
int			check_path(t_shell *bash);

//test_execution.c
void		init_tree1(char **argv, t_shell *bash);
void		init_tree2(char **argv, t_shell *bash);
void		init_tree3(char **argv, t_shell *bash);
void		free_lstcmds(t_shell *bash);

//utils_exec.c
void		exec_child(char *cmd_path, char **cmd, t_shell *bash);
void		exec_cmd(int *fd, char *cmd_path, t_lstcmd *struct_cmd, \
t_shell *bash);
char		*ft_fork(int *fd, char *cmd_path, t_lstcmd *struct_cmd, \
t_shell *bash);
void		pipe_loop(t_tree *tree, t_shell *bash);
void		pipe_loop2(t_shell *bash, t_lstcmd *cmds, int *fd);	
int			wait_loop(t_tree *tree, t_shell *bash);

//utils2_exec.c
int			exec_without_fork(t_tree *tree, t_shell *bash);
void		exec_cmd2(t_lstcmd *struct_cmd, t_shell *bash, char *cmd_path);
//utils_signal.c
void		init_signal(void);
void		init_signal_child(void);
void		init_signal_ign(void);
int			manage_signal(int status, int exit_status);
void		init_signal_here(void);

#endif
