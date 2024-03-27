/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_utils_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:15:55 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/27 21:42:54 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstcmd	*box_cmd(t_infopars	*lst)
{
	t_lstcmd	*new_cmd;
	t_infopars	*curr;
	int			i;

	new_cmd = malloc(sizeof(new_cmd));
	if (!new_cmd)
		return (NULL);
	lib_memset(new_cmd, 0, sizeof(new_cmd));
	i = 0;
	new_cmd->out_file = -1;
	new_cmd->in_file = -1;
	new_cmd->child = -1;
	curr = lst;
	new_cmd->cmd = malloc(sizeof(char *) * (len_cmd(lst) + 1));
	if (!new_cmd->cmd)
		return (NULL);
	while (curr && (curr->spe != 1 || curr->spe != 5 || curr->spe != 0))
	{
		if (curr->spe == 2)
			new_cmd->str[i++] = curr->str;
		curr = curr->next;
	}
	new_cmd->str[i] = NULL;
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
