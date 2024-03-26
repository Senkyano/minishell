/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_utils_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:15:55 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/26 19:43:09 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstcmd	*box_cmd(char **str)
{
	t_lstcmd	*new_cmd;

	new_cmd = malloc(sizeof(new_cmd));
	if (!new_cmd)
		return (NULL);
	lib_memset(new_cmd, 0, sizeof(new_cmd));
	new_cmd->out_file = -1;
	new_cmd->in_file = -1;
	new_cmd->child = -1;
	new_cmd->cmd = str;
	return (new_cmd);
}

void	add_lstcmd(t_lstcmd **lst_cmd, t_lstcmd *new_cmd)
{
	t_lstcmd	*curr;

	if (!(*lst_cmd))
		(*lst_cmd) = new_cmd;
	else if ((*lst_cmd))
	{
		curr = (*lst_cmd);
		while (curr->next)
			curr = curr->next;
		curr->next = new_cmd;
	}
}
