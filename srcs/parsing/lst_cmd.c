/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:38 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/02 23:26:27 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_lstcmd	*box_cmd(char *cmd, t_lstfd *fd_cmd, t_shell *bash)
{
	t_lstcmd	*new_cmd;

	lib_memset(new_cmd, 0, sizeof(new_cmd));
	new_cmd->lst_fd = fd_cmd;
	return (new_cmd);
}

void	add_lstcmd(t_body *process, t_lstcmd *cmd)
{
	t_lstcmd	*curr_cmd;

	curr_cmd = process->allcmd;
	if (!process->allcmd)
	{
		process->allcmd = cmd;
		return ;
	}
	while (curr_cmd->next != NULL)
		curr_cmd = curr_cmd->next;
	curr_cmd->next = cmd;
}
