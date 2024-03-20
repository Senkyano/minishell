/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:38 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 16:55:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_lstcmd	*box_cmd(char **cmd, t_lstfd *fd_cmd, t_shell *bash)
{
	t_lstcmd	*new_cmd;
	int			i;

	new_cmd = malloc(sizeof(t_lstcmd));
	if (!new_cmd)
		return (NULL);
	i = -1;
	lib_memset(new_cmd, 0, sizeof(new_cmd));
	new_cmd->t_path = malloc(sizeof(char *) * (bash->nbr_path + 1));
	if (!new_cmd->t_path)
		return (free(new_cmd), NULL);
	while (bash->path[++i])
	{
		new_cmd->t_path[i] = str_join(bash->path[i], cmd[1]);
		if (!new_cmd->t_path[i])
			return (lib_free_split(new_cmd->t_path), NULL);
	}
	new_cmd->t_path[i] = NULL;
	new_cmd->lst_fd = fd_cmd;
	new_cmd->cmd = cmd;
	return (new_cmd);
}

void	add_or(t_lstcmd **process_or, t_lstcmd *def_cmd)
{
	t_lstcmd	*process_cur;

	if (!(*process_or))
		(*process_or) = def_cmd;
	else
	{
		process_cur = (*process_or);
		while (process_cur->or_next)
			process_cur = process_cur->or_next;
		process_cur->or_next = def_cmd;
	}
}

void	add_and(t_lstcmd **process_and, t_lstcmd *def_cmd)
{
	t_lstcmd	*process_cur;

	if (!(*process_and))
		(*process_and) = def_cmd;
	else
	{
		process_cur = (*process_and);
		while (process_cur->and_next)
			process_cur = process_cur->and_next;
		process_cur->and_next = def_cmd;
	}
}

void	add_default(t_lstcmd **lst_cmd, t_lstcmd *cmd)
{
	t_lstcmd	*curr_lst;

	if (!(*lst_cmd))
		(*lst_cmd) = cmd;
	else
	{
		curr_lst = (*lst_cmd);
		while (curr_lst->def_next)
			curr_lst = curr_lst->def_next;
		curr_lst->def_next = cmd;
	}
}
