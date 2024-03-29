/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/29 14:18:59 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
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
			tree->lst_cmd = tree->lst_cmd->def_next;
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
	if (bash->lst_char)
		free_strshell(&bash->lst_char);
	if (bash->lstcmd)
		free_lstcmds(bash);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
	if (bash->tree)
		free_tree(bash->tree);
	if (bash->str_split)
		free(bash->str_split);
}
