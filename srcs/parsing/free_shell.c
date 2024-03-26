/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/26 15:14:32 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	free_shell(t_shell *bash)
{
	if (bash->path)
		lib_free_split(bash->path);
	if (bash->str_split)
		lib_free_split(bash->str_split);
	if (bash->lst_char)
		free_boxshell(&bash->lst_char);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
}

void	free_tree(t_tree *curr)
{
	if (curr->left_child)
		free_tree(curr->left);
	if (curr->right_child)
		free_tree(curr->right_child);
	if (curr->type == 1 || curr->type == 2)
		free(curr);
	else if (curr->type == 3)
		free_lst_cmd();
}
