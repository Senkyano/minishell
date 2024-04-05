/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/05 19:31:55 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*second_tree(t_infopars	*lstchar, t_tree *parent_branch, int parenthese)
{
	t_tree	*new_branch;
	t_tree	*tmp_branch;
	t_infopars	*curr;

	if (parenthese == 0)
		curr = check_point(lst_char, parenthese);
	if (curr->spe == 1)
	{
		new_branch = build_branch(curr);
		if (!new_branch)
			return (NULL);
		if (!parent_branch)
			parent_branch = new_branch;
		else if (parent_branch)
		{
			parent_branch->left_child = new_branch;
			new_branch->parent = parent_branch;
		}
		if (/*si noeud derriere*/)
		{
			tmp_branch = second_tree(curr, new_branch, parenthese);
			if (!tmp_branch)
				return (NULL);
			else if (tmp_branch)
			{
				new_branch->left_child = tmp_branch;
				tmp_branch->parent = new_branch;
			}
		}
		if (curr->next && curr->next->spe != 0)
			tmp_branch = build_branch(curr->next);
		// else if (curr->next && curr->next->spe == 0)
		// {
			// tmp_branch = second_tree(curr, new_branch, parenthese + 1)
		// }
		if (!tmp_branch)
			return (NULL);
		else if (tmp_branch)
		{
			new_branch->right_child = tmp_branch;
			tmp_branch->parent = new_branch;
		}
		return (new_branch);
	}
	else if (curr && curr->spe != 1)
	{
		if (curr->spe != 0)
			tmp_branch = build_branch(curr);
		// else if (curr->spe == 0)
		// {
			// tmp_branch = second_tree(curr, parent_branch, );
		// }
		if (!tmp_branch)
			return (NULL);
		if (!parent_branch)
			parent_branch = tmp_branch;
		else if (parent_branch)
		{
			parent_branch->left_child = tmp_branch;
			tmp_branch->parent = parent_branch;
		}
	}
	return (parent_branch);
}

t_infopars	*check_point(t_infopars *lst_char, int par)
{
	t_infopars	*curr;
	int			parenthese;

	curr = lst_char;
	parenthese =  par;
	while (curr->prec)
	{
		if (curr->spe == 1)
			return (curr);
		curr = curr->prec;
	}
	return (curr);
}

t_infopars	*last_elecmd(t_infopars *curr)
{
	
}
