/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_essential.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:54:23 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 16:27:40 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_essential(t_shell *bash)
{
	if (bash->lst_char)
	{
		free_boxshell(&bash->lst_char);
		bash->lst_char = NULL;
	}
	if (bash->tree)
	{
		free_tree(bash->tree);
		bash->tree = NULL;
	}
}

void	free_cmds_era(t_lstcmd *cmd)
{
	t_lstcmd	*curr;

	while (cmd)
	{
		curr = cmd;
		cmd = cmd->next;
		free(curr);
	}
}

void	free_tree_era(t_tree *curr)
{
	t_lstcmd	*curr_cmd;

	if (curr->left_child)
		free_tree_era(curr->left_child);
	if (curr->right_child)
		free_tree_era(curr->right_child);
	if (curr->type == LST_CMD)
	{
		while (curr->lst_cmd)
		{
			curr_cmd = curr->lst_cmd;
			curr->lst_cmd = curr->lst_cmd->next;
			if (curr_cmd->in_file > 0)
				close(curr_cmd->in_file);
			if (curr_cmd->out_file > 0)
				close(curr_cmd->out_file);
			free(curr_cmd->cmd);
			free(curr_cmd);
		}
		free(curr);
	}
	else if (curr->type == OPERATOR_AND || curr->type == OPERATOR_OR)
		free(curr);
}

void	eradication(t_shell *bash)
{
	if (bash->lst_char)
		free_boxshell(&bash->lst_char);
	if (bash->tree)
		free_tree_era(bash->tree);
	if (bash->path)
		lib_free_split(bash->path);
	if (bash->str_split)
		lib_free_split(bash->str_split);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
	close(bash->std_in);
	close(bash->std_out);
	exit(bash->exit_status);
}
