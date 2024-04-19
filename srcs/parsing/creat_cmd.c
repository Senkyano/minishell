/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:56:30 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/19 10:54:50 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_cmd(t_infopars	*lst);
static void	init_cmd(t_lstcmd *cmd, int index);

t_lstcmd	*build_cmd(t_infopars *lst, int index)
{
	t_lstcmd	*info_cmd;
	int			i;
	t_infopars	*curr;

	info_cmd = malloc(sizeof(t_lstcmd));
	if (!info_cmd)
		return (NULL);
	init_cmd(info_cmd, index);
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
	info_cmd->available = 1;
	return (info_cmd);
}

static void	init_cmd(t_lstcmd *cmd, int index)
{
	cmd->error = 0;
	cmd->index = index;
	cmd->max_index = 0;
	cmd->available = 0;
	cmd->cmd = NULL;
	cmd->t_path = NULL;
	cmd->child = 0;
	cmd->last_infile = 0;
	cmd->in_file = 0;
	cmd->in_file_name = NULL;
	cmd->out_file = 0;
	cmd->next = NULL;
	cmd->prec = NULL;
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
