/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:32:43 by rihoy             #+#    #+#             */
/*   Updated: 2024/02/29 18:35:55 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include "../utils/lib_utils.h"

typedef struct	s_lstcmd
{
	char			**cmd;	  // cmd
	char			**t_path; // true path
	pid_t			child;	  // child
	struct s_lstcmd	*next;
}	t_lstcmd;

// typedef struct	s_body
// {
// 	t_lstcmd			*
// 	struct s_lstprio	*next;
// }	t_body;

typedef struct	s_shell
{
	int			exit_status;
	char		**path;
	t_lstcmd	*allcmd;
}	t_shell;

void	launch_shell(int argc, const char **env);

#endif
