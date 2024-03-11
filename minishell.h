/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:01:00 by yrio              #+#    #+#             */
/*   Updated: 2024/02/21 13:28:43 by yrio             ###   ########.fr       */
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
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_cmdline {
	int					index;
	int					type;
	char				*elem;
	char				*path_cmd;
	char				**spliting_cmd_args;
	struct s_cmdline	*next;
}					t_cmdline;

typedef struct t_list {
	int				index;
	char			*key;
	char			*value;
	char			**splitting;
	struct t_list	*next;
}					t_envlist;

typedef struct s_minishell
{
	struct s_cmdline	*cmdline;
	char				*infile_name;
	char				*outfile_name;
	struct t_list		*lst_envs;
	int					*pid;
	int					total_cmd;
	int					fd_infile;
	int					fd_outfile;
	int					error_init;
	int					recup;
}					t_minishell;

char		*ft_strjoin(char const *s1, char const *s2);
char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, unsigned int n);
char		**ft_free(char **char_tab, int nb_words);

void		ft_cd(char **argv, t_minishell *minishell);
void		ft_pwd(void);
void		ft_unset(char **args_split, t_minishell *minishell);
int			ft_export(char	**args_split, t_minishell *minishell);
void		ft_echo(char **args_split);
void		ft_exit(char **args_split);

void		ft_env(t_minishell *minishell);
int			check_env_key(t_minishell *minishell, char *str);
char		*get_value_env(t_minishell *minishell, char *key);

t_envlist	*lst_new_env(char *str);
t_cmdline	*new_elem_cmdline(int tmp, char **argv, t_minishell *minishell);
void		lstadd_back(t_envlist *new, t_envlist *lst);
void		lstclear(t_envlist *lst);
t_envlist	*lst_index(t_envlist *lst, int index);

void		ls_cmd(void);
char		**get_paths(char **env);
char		**free_split(char **char_tab);
void		malloc_env(t_minishell *minishell, char **env);
char		**ft_split_onedel(char const *s, char c);

#endif
