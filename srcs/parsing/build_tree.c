/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:13:16 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/28 17:08:26 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*building_tree(t_infopars *lst, t_tree *tree)
{
	t_tree	*tmp;

	if ()
		tmp = // aller tout a gauche de la liste chaine sur le dernier process;
	if ()
		// mettre les processus
	if ()
		// prendre la partie de gauche et dire que le processus 
}

t_tree	*build_branch(t_infopars *lst)
{
	t_tree	*new_branch;

	new_branch = malloc(sizeof(new_branch));
	if (!new_branch)
		return (NULL);
	lib_memset(&token, 0, sizeof(new_branch));
	if (lst->spe == 1)
	{
		if (lst->str[0] == '&')
			new_branch->type = 1;
		else if (lst->str[0] == '|')
			new_branch->type = 2;
	}
	else if (lst->spe == 2)
	{
		new_branch->type = 3;
		new_branch->lst_cmd = box_cmd(lst);
		if (!new_branch->lst_cmd)
			return (NULL);
	}
	return (new_branch);
}
