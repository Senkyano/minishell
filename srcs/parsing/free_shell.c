/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 17:53:51 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	free_tree(t_tree *tree)
{
	t_lstcmd *tmp_lst_cmd;

	if (tree->left_child)
		free_tree(tree->left_child);
	if (tree->right_child)
		free_tree(tree->right_child);
	if (tree->type == LST_CMD)
	{
		while (tree->lst_cmd)
		{
			tmp_lst_cmd = tree->lst_cmd;
			tree->lst_cmd = tree->lst_cmd->next;
			if (tmp_lst_cmd)
				lib_free_split(tmp_lst_cmd->cmd);
			free(tmp_lst_cmd);
		}
		free(tree);
	}
	else if (tree->type == OPERATOR_AND || tree->type == OPERATOR_OR)
		free(tree);
}

void	free_shell(t_shell *bash)
{
	if (bash->path)
		lib_free_split(bash->path);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
	if (bash->tree)
		free_tree(bash->tree);
	if (bash->str_split)
		free(bash->str_split);
}

// void	free_tree(t_tree *curr)
// {
// 	if (curr->left_child)
// 		free_tree(curr->left);
// 	if (curr->right_child)
// 		free_tree(curr->right_child);
// 	if (curr->type == 1 || curr->type == 2)
// 		free(curr);
// 	else if (curr->type == 3)
// 		free_lst_cmd();
// }
