/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:32:43 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/05 18:51:18 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>

// colors
#define BLK "\e[0;90m"
#define RED "\e[1;31m" // ERROR
#define GR "\e[1;92m"
#define Y "\e[1;93m"
#define BLU "\e[1;94m" //Minishell name
#define PUR "\e[1;95m"
#define CY "\e[1;96m"
#define WH "\e[0;97m"
#define RST "\e[0m"

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

typedef struct	s_lstcmd // quelque soit la liste il y auras de le default lst de base
{
	bool			proc_or;
	bool			proc_and;
	bool			proc_def;
	char			**cmd;	  // cmd
	char			**t_path; // true path
	pid_t			child;	  // child sous-process
	t_lstfd			*lst_fd;
	struct s_lstcmd	*def_next;
	struct s_lstcmd	*and_next; // si def a reussis a etre exectuer comme il faut alors continue dans and
	struct s_lstcmd	*or_next; // si ou existe ne rentre pas si def a reussis a etre exectuer comme il faut
}	t_lstcmd;

typedef struct	s_shell
{
	int			exit_status; // gestion des erreur
	char		**path; // True path
	char		**space;
	t_lstcmd	*lstcmd;
}	t_shell;
// Erreur
void		launch_shell(int argc, const char **env);
void		gestion_exit(char *msg, t_shell *bash);
bool		valid_str(char *str);
// Get
void		get_true_path(t_shell *bash, char const **env);
// Process add
void		add_or(t_lstcmd *process_or, t_lstcmd *def_cmd);
void		add_and(t_lstcmd *process_and, t_lstcmd *def_cmd);
void		add_default(t_lstcmd *lst_cmd, t_lstcmd *cmd);
// Cmd
t_lstcmd	*box_cmd(char *cmd, t_lstfd *fd_cmd, t_shell *bash);
// In
void	in_sgquote(char c, t_token *token);
void	in_doquote(char c, t_token *token);
void	in_parsing(char c, t_token *token);



// test
int			cutting(char *str, t_lstcmd *base);

#endif
