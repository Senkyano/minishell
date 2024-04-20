/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:47:48 by yrio              #+#    #+#             */
/*   Updated: 2024/04/20 17:35:41 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		close_cmds(t_lstcmd *lstcmd);
t_lstcmd	*first_cmd_pipe(t_lstcmd *lstcmd);

void	close_tree(t_tree *curr)
{
	if (curr)
	{
		if (curr->left_child)
			close_tree(curr->left_child);
		if (curr->right_child)
			close_tree(curr->right_child);
		if (curr->lst_cmd)
			close_cmds(curr->lst_cmd);
	}
}

void	close_out_heredoc(t_shell *bash, int fd, t_lstcmd *lstcmd)
{
	t_lstcmd	*first;

	if (lstcmd)
	{
		first = first_cmd_pipe(lstcmd);
		if (first)
			close_cmds(first);
	}
	close_tree(bash->tree);
	if (fd > 0)
		close(fd);
	if (bash->std_in)
		close(bash->std_in);
	if (bash->std_out)
		close(bash->std_out);
}

t_lstcmd	*first_cmd_pipe(t_lstcmd *lstcmd)
{
	t_lstcmd	*cmd;

	cmd = lstcmd;
	while (cmd->prec)
		cmd = cmd->prec;
	return (cmd);
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
