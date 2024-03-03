/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:32:43 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/03 13:40:40 by rihoy            ###   ########.fr       */
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

typedef struct s_lstfd
{
	char			*name;
	bool			in_file;
	bool			here_doc;
	int				fd;
	struct s_lstfd	*next;
}	t_lstfd;

typedef struct	s_lstcmd
{
	char			**cmd;	  // cmd
	char			**t_path; // true path
	pid_t			cmd_child;	  // child sous-process
	t_lstfd			*lst_fd;
	struct s_lstcmd	*next;
}	t_lstcmd;

typedef struct	s_body
{
	int				prio; //prio sur le process
	pid_t			body_child; // child main process
	t_lstcmd		*allcmd; //Commande entre pipe
	struct s_body	*next; //process suivant
}	t_body;

typedef struct	s_shell
{
	int			exit_status; // gestion des erreur
	char		**path; // True path
	char		**space;
	t_body		*process;
}	t_shell;
// Erreur
void		launch_shell(int argc, const char **env);
void		gestion_exit(char *msg, t_shell *bash);
// Get
void		get_true_path(t_shell *bash, char const **env);
// Process
void		add_proccess(t_shell *bash, t_body *process);
t_body		*bloc_process(t_lstcmd *lstcmd, int prio);
// Cmd
t_lstcmd	*box_cmd(char *cmd, t_lstfd *fd_cmd, t_shell *bash);
void		add_lstcmd(t_body *process, t_lstcmd *cmd);

#endif
