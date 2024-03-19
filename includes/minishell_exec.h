/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:01:00 by yrio              #+#    #+#             */
/*   Updated: 2024/03/19 16:58:57 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

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

extern int	g_last_exit_code;

typedef struct t_list {
	int				index;
	char			*key;
	char			*value;
	char			**splitting;
	struct t_list	*next;
}				t_envlist;

typedef struct s_token
{
	bool			in_cmd;
	bool			in_doquote;
	bool			in_sgquote;
	bool			error;
	int				in_par;
	bool			in_process;
	bool			enter_par;
}	t_token;

typedef struct s_lstfd
{
	// char			*name; pour que se soit bien securiser mais on as pas forcement besoin en realite
	bool			in_file;
	bool			out_file;
	bool			file_here;
	int				fd;
	struct s_lstfd	*next;
}	t_lstfd;

typedef struct s_lsthere
{
	int					fd[2];
	char				*lim;
	struct s_lsthere	*next;
}	t_lsthere;

typedef struct	s_infopars
{
	int		spe; // 1 = file, 2 = redirection, 3 = cmd, 4 = pipe, 5 = process_and, 6 = process_or, 7 = variable env.
	char	*str;
	// pour le parsing attribuer token
	struct s_infopars	*next;
	struct s_infopars	*prec;
}	t_infopars;

typedef struct	s_lstcmd // quelque soit la liste il y auras de le default lst de base
{
	int				error;		// pour des cas specifique
	int				index;		// index pour les pipes
	char			**cmd;	  // cmd
	char			**t_path; // true path
	pid_t			child;	  // child sous-process
	t_lstfd			*lst_fd;
	struct s_lstcmd	*def_next; //pipe
	struct s_lstcmd	*and_next; // si def a reussis a etre exectuer comme il faut alors continue dans and
	struct s_lstcmd	*or_next; // si ou existe ne rentre pas si def a reussis a etre exectuer comme il faut
}	t_lstcmd;

typedef struct	s_shell
{
	t_token		tok_ge;
	int			exit_status; // gestion des erreur
	char		**path; // True path
	int			nbr_path;
	t_envlist	*lst_envs;
	char		**str_split;
	t_lstcmd	*lstcmd;
	t_infopars	*lst_char;
}	t_shell;

typedef struct s_data
{
	char 		*tmp;
	char		*new_str;
	int			i;
	t_infopars	*new_lst;
	t_infopars	*tmp_box;
}	t_data;

// Erreur
void		launch_shell(int argc, const char **env);
void		gestion_exit(char *msg, t_shell *bash);
bool		valid_str(char *str);
bool		valid_token(char *str);
bool		check_process(t_infopars *pars);
// Get
void		get_true_path(t_shell *bash, char const **env);
// Case
t_infopars	*diff_boxshell(char *str, int spe);
t_lstcmd	*box_cmd(char **cmd, t_lstfd *fd_cmd, t_shell *bash);
t_infopars	*cut_boxshell(char *str);
t_infopars	*first_boxshell(t_infopars *last);
// Process manipulation
t_infopars	*supp_blockshell(t_infopars *pre, t_infopars *next, t_infopars *curr);
// Process add
bool		build_process(char *str, t_shell *bash);
void		add_or(t_lstcmd **process_or, t_lstcmd *def_cmd);
void		add_and(t_lstcmd **process_and, t_lstcmd *def_cmd);
void		add_default(t_lstcmd **lst_cmd, t_lstcmd *cmd);
void		add_boxshell(t_infopars **all, t_infopars *part);
void		add_btw_boxshell(t_infopars *pre, t_infopars *new_lst, \
t_infopars *next, t_infopars **old);
// Free process
void		free_def_process(t_lstcmd *lstcmd);
void		free_or_process(t_lstcmd *lstprocess);
void		free_and_process(t_lstcmd *lstprocess);
void		free_boxshell(t_infopars **all);
void		free_shell(t_shell *bash);
void		free_blockstrshell(t_infopars *selec);
// Print process
void		print_strshell(t_infopars *lst);
// In
void		in_sgquote(char c, t_token *token);
void		in_doquote(char c, t_token *token);
void		in_parsing(char c, t_token *token);
void		in_process(char c, t_token *token);
// split minishell
int			count_minishell(char *str);
char		**split_minishell(char *str);
// test
int			cutting(char *str, t_lstcmd *base);
// SKIP
int			skip_space(char *str);
int			skip_char(char *str);
int			skip_not_env(char *str);
int			name_env(char *str);
int			skip_insert_env(char *str, char c);
// ENV
char		*insert_env(char *str, t_shell *bash);
// DOMAINE Analysis
void		analysis_shell(t_shell *bash);
bool		malloc_proc(t_data *tmp, char *str);
int			next_process(char *str);













// char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_gnl(char *s1, char *s2, size_t size);
// char		*get_next_line(int fd);
// char		*ft_strchr(const char *s, int c);
// char		*ft_substr(char const *s, unsigned int start, size_t len);
// char		**ft_split(char const *s, char c);
// int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
char		**ft_free(char **char_tab, int nb_words);

void		launch_builtins(t_shell *bash);
void		ft_cd(char **argv, t_shell *minishell);
void		ft_pwd(void);
void		ft_unset(char **args_split, t_shell *minishell);
int			ft_export(char	**args_split, t_shell *minishell);
void		ft_echo(char **args_split);
void		ft_exit(t_shell *bash);

void		ft_env(t_shell *minishell);
int			check_env_key(t_shell *minishell, char *str);
char		*get_value_env(t_shell *minishell, char *key);

t_envlist	*lst_new(char *str);
void		lstadd_back(t_envlist *new, t_envlist *lst);
void		lstclear(t_envlist *lst);
t_envlist	*lst_index(t_envlist *lst, int index);

void		ls_cmd(void);
char		**get_paths(char **env);
char		**free_split(char **char_tab);
void		malloc_env(t_shell *minishell, const char **env);
char		**ft_split_onedel(char const *s, char c);
int			close_minishell(char **args_split, t_shell *minishell);

#endif
