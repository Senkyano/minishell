/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:01:00 by yrio              #+#    #+#             */
/*   Updated: 2024/03/29 11:38:02 by yrio             ###   ########.fr       */
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

# define OPERATOR_AND 1
# define OPERATOR_OR 2
# define LST_CMD 3

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
	bool			process_or;
	bool			process_and;
}	t_token;

typedef struct s_lstfd
{
	char			*name;
	bool			in_file;
	bool			here_doc;
	int				fd;
	struct s_lstfd	*next;
}	t_lstfd;

typedef struct	s_infopars
{
	int		spe; // 1 = file, 2 = redirection, 3 = cmd, 4 = pipe, 5 = process_and, 6 = process_or, 7 = variable env.
	char	*str;
	// pour le parsing attribuer token
	struct s_infopars	*next;
}	t_infopars;

typedef struct	s_lstcmd // quelque soit la liste il y auras de le default lst de base
{
	int				index;	// index pour les pipes
	char			**cmd;	  // cmd
	char			**t_path; // true path
	pid_t			child;	  // child sous-process
	t_lstfd			*lst_fd;
	struct s_lstcmd	*def_next; //pipe
	struct s_lstcmd	*and_next; // si def a reussis a etre exectuer comme il faut alors continue dans and
	struct s_lstcmd	*or_next; // si ou existe ne rentre pas si def a reussis a etre exectuer comme il faut
}	t_lstcmd;

typedef	struct s_tree
{
	int				type;
	struct s_tree	*parent;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
	struct s_lstcmd	*lst_cmd;
	//struct s_tree	*next;
}					t_tree;

typedef struct	s_shell
{
	int			exit_status; // gestion des erreur
	char		**path; // True path
	int			std_out;
	int			std_in;
	int			nbr_path;
	int			len_cmds;
	char		**env;
	t_envlist	*lst_envs;
	char		**str_split;
	t_lstcmd	*lstcmd;
	t_infopars	*lst_char;
	t_tree		*tree;
}	t_shell;

// Erreur
void		launch_shell(int argc, const char **env);
void		gestion_exit(char *msg, t_shell *bash);
bool		valid_str(char *str);
// Get
void		get_true_path(t_shell *bash, char const **env);
// Case
t_infopars	*diff_strshell(char *str, int spe);
t_lstcmd	*box_cmd(char **cmd, t_lstfd *fd_cmd, t_shell *bash);
// Process add
void		build_process(char *str, t_shell *bash);
void		add_or(t_lstcmd **process_or, t_lstcmd *def_cmd);
void		add_and(t_lstcmd **process_and, t_lstcmd *def_cmd);
void		add_default(t_lstcmd **lst_cmd, t_lstcmd *cmd);
void		add_strshell(t_infopars **all, t_infopars *part);
// Free process
void		free_def_process(t_lstcmd *lstcmd);
void		free_or_process(t_lstcmd *lstprocess);
void		free_and_process(t_lstcmd *lstprocess);
void		free_strshell(t_infopars **all);
void		free_shell(t_shell *bash);
void		free_tree(t_tree *tree);
// Print process
void		print_strshell(t_infopars *lst);
// In
void		in_sgquote(char c, t_token *token);
void		in_doquote(char c, t_token *token);
void		in_parsing(char c, t_token *token);
// split minishell
int			count_minishell(char *str);
char		**split_minishell(char *str);
// test
int			cutting(char *str, t_lstcmd *base);

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
void		ft_cd(char **argv, t_shell *minishell);
void		ft_pwd(void);
void		ft_unset(char **args_split, t_shell *minishell);
int			ft_export(char	**args_split, t_shell *minishell);
void		ft_echo(char **args_split);
void		ft_exit(char **cmd, t_shell *bash);
int			ft_env(char **args_split, t_shell *minishell);

int			check_env_key(t_shell *minishell, char *str);
char		*get_value_env(t_shell *minishell, char *key);

//lst_utils.c
t_envlist	*lst_new(char *str);
void		lstadd_back(t_envlist *new, t_envlist *lst);
void		lstclear(t_envlist *lst);
t_envlist	*lst_index(t_envlist *lst, int index);
int			lst_size(t_lstcmd *lstcmd);

//builtins_utils.c
int			exec_builtins(char **cmd, t_shell *bash);
int			is_builtins(char **cmd);
void		launch_builtins(int std_out, int *fd, t_lstcmd *cmds, t_shell *bash);

//utils_minishell.c
void		ls_cmd(void);
char		**get_paths(char **env);
char		**free_split(char **char_tab);
void		malloc_env(t_shell *minishell, char **env);
char		**ft_split_onedel(char const *s, char c);
char		*check_cmd(char *cmd, char **path_split);

//test_execution.c
void		init_tree(char **argv, t_shell *bash);
void		free_lstcmds(t_shell *bash);

//utils_exec.c
void	exec_child(char *cmd_path, char **cmd, t_shell *bash);
int		exec_cmdbash(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash);

#endif
