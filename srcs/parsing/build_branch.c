/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:16 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/20 17:44:52 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_branch(t_infopars *lstchar, t_shell *bash)
{
	t_tree	*new_branch;

	new_branch = malloc(sizeof(t_tree));
	if (!new_branch)
		return (NULL);
	new_branch->parent = NULL;
	new_branch->left_child = NULL;
	new_branch->right_child = NULL;
	new_branch->lst_cmd = NULL;
	if (lstchar->spe == 1)
	{
		if (lstchar->str[0] == '&')
			new_branch->type = 1;
		else if (lstchar->str[0] == '|')
			new_branch->type = 2;
		new_branch->lst_cmd = NULL;
	}
	else if (lstchar->spe != 1)
	{
		new_branch->type = 3;
		new_branch->lst_cmd = create_lstcmd(lstchar, bash, new_branch);
		if (!new_branch->lst_cmd)
			return (NULL);
	}
	return (new_branch);
}

void	free_branch(t_tree *branch)
{
	if (branch->lst_cmd)
		free_lstcmd(branch->lst_cmd);
	free(branch);
}
