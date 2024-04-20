/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lstcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:42:33 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/20 17:44:05 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_infopars	*next_pipe(t_infopars *lst);
static bool			exist_next_pipe(t_infopars *lst);
static void			add_lstcmd(t_lstcmd **lst_cmd, t_lstcmd *new_cmd);

t_lstcmd	*create_lstcmd(t_infopars *lst, t_shell *bash, t_tree *branch)
{
	t_infopars	*curr;
	t_lstcmd	*tmp_cmd;
	int			i;

	curr = lst;
	i = 0;
	while (curr)
	{
		tmp_cmd = build_cmd(curr, i++);
		if (!tmp_cmd)
		{
			free_lstcmd(branch->lst_cmd);
			return (NULL);
		}
		add_lstcmd(&branch->lst_cmd, tmp_cmd);
		if (!define_last(curr, tmp_cmd, bash, branch)) // envoyer branch
			return (branch->lst_cmd);
		if (!exist_next_pipe(curr))
			return (branch->lst_cmd);
		curr = next_pipe(curr);
	}
	return (branch->lst_cmd);
}

void	free_lstcmd(t_lstcmd *lst)
{
	t_lstcmd	*curr;

	while (lst)
	{
		curr = lst;
		lst = lst->next;
		if (curr->in_file)
			close(curr->in_file);
		if (curr->out_file)
			close(curr->out_file);
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
	new_cmd->prec = curr;
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
