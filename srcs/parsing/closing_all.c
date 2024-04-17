/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:48 by yrio              #+#    #+#             */
/*   Updated: 2024/04/17 14:56:30 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmds(t_lstcmd *lstcmd);

void	close_tree(t_tree *curr)
{
	if (curr->left_child)
		close_tree(curr->left_child);
	if (curr->right_child)
		close_tree(curr->right_child);
	if (curr->lst_cmd)
		close_cmds(curr->lst_cmd);
}

void	close_cmds(t_lstcmd *lstcmd)
{
	t_lstcmd	*curr;

	curr = lstcmd;
	while (curr)
	{
		if (curr->in_file > 0)
			close(curr->in_file);
		if (curr->out_file > 0)
			close(curr->out_file);
		curr = curr->next;
	}
}
