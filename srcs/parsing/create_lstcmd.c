/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lstcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:42:33 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 12:21:44 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_infopars	*next_pipe(t_infopars *lst);
static bool			exist_next_pipe(t_infopars *lst);
static void			add_lstcmd(t_lstcmd **lst_cmd, t_lstcmd *new_cmd);

t_lstcmd	*create_lstcmd(t_infopars *lst)
{
	t_infopars	*curr;
	t_lstcmd	*tmp_cmd;
	t_lstcmd	*new_lst;

	curr = lst;
	new_lst = NULL;
	while (curr)
	{
		tmp_cmd = build_cmd(curr);
		if (!tmp_cmd)
		{
			free_lstcmd(new_lst);
			return (NULL);
		}
		add_lstcmd(&new_lst, tmp_cmd);
		if (!exist_next_pipe(curr))
			return (new_lst);
		curr = next_pipe(curr);
	}
	return (new_lst);
}

void	free_lstcmd(t_lstcmd *lst)
{
	t_lstcmd	*curr;

	while (lst)
	{
		curr = lst;
		lst = lst->next;
		if (curr->cmd)
			free(curr->cmd);
		free(curr);
	}
}

static void	add_lstcmd(t_lstcmd **lst_cmd, t_lstcmd *new_cmd)
{
	t_lstcmd	*curr;

	if (!(*lst_cmd))
	{
		(*lst_cmd) = new_cmd;
		return ;
	}
	curr = (*lst_cmd);
	while (curr->next)
		curr = curr->next;
	curr->next = new_cmd;
}

static bool	exist_next_pipe(t_infopars *lst)
{
	t_infopars	*curr;

	curr = lst;
	while (curr && curr->spe != 0 && curr->spe != 1)
	{
		if (curr->spe == 5)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static t_infopars	*next_pipe(t_infopars *lst)
{
	t_infopars	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->spe == 5 && curr->next)
		{
			curr = curr->next;
			return (curr);
		}
		curr = curr->next;
	}
	return (curr);
}
