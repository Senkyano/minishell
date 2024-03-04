/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:32:43 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/04 22:01:02 by rihoy            ###   ########.fr       */
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
	bool			in_par;
	bool			new_process;
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
	struct s_lstcmd	*and_next;
	struct s_lstcmd	*or_next;
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
// Get
void		get_true_path(t_shell *bash, char const **env);
// Process
// Cmd
t_lstcmd	*box_cmd(char *cmd, t_lstfd *fd_cmd, t_shell *bash);





// test
int			cutting(char *str, t_lstcmd *base);

#endif
