/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:56:30 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/11 18:57:21 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_cmd(t_infopars	*lst);

t_lstcmd	*build_cmd(t_infopars *lst, int index)
{
	t_lstcmd	*info_cmd;
	int			i;
	t_infopars	*curr;

	info_cmd = malloc(sizeof(t_lstcmd));
	if (!info_cmd)
		return (NULL);
	lib_memset(info_cmd, 0, sizeof(info_cmd));
	info_cmd->cmd = malloc(sizeof(char *) * (size_cmd(lst) + 1));
	if (!info_cmd->cmd)
		return (free(info_cmd), NULL);
	curr = lst;
	i = 0;
	while (curr && curr->spe != 5 && curr->spe != 1 && curr->spe != 0)
	{
		if (curr->spe == 2)
			info_cmd->cmd[i++] = curr->str;
		curr = curr->next;
	}
	info_cmd->cmd[i] = NULL;
	info_cmd->next = NULL;
	info_cmd->index = index;
	info_cmd->in_file_name = NULL;
	info_cmd->available = 1;
	return (info_cmd);
}

void	print_lstcmd(t_lstcmd *lstcmd)
{
	t_lstcmd	*curr;
	int			i;

	curr = lstcmd;
	while (curr)
	{
		i = 0;
		while (curr->cmd[i])
			printf_error("%s\n", curr->cmd[i++]);
		curr = curr->next;
	}
}

static int	size_cmd(t_infopars	*lst)
{
	t_infopars	*curr;
	int			i;

	i = 0;
	curr = lst;
	while (curr)
	{
		if (curr->spe == 2)
			i++;
		if (curr->spe == 5 || curr->spe == 0 || curr->spe == 1)
			return (i);
		curr = curr->next;
	}
	return (i);
}
