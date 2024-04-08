/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:03:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/08 17:27:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	building_tree(t_tree **curr_tree, t_infopars *last_ele)
{
	t_infopars	*curr;
	t_tree		*new_branch;

	curr = noeud_first(last_ele);
	if (curr->spe == 1) // si c'est un noeud on vas cree le noeud.
	{
		new_branch = build_branch(curr);
		if (!new_branch)
			return (false);
		if (!(*curr_tree))
			(*curr_tree) = new_branch;
		else
		{
			(*curr_tree)->left_child = new_branch;
			new_branch->parent = (*curr_tree);
		}
	}
	else // si c'est pas un noeud alors on vas creer la liste de commande.
	{
		if (curr != 0)
		{
			new_branch = build_branch(curr);
			if (!new_branch)
				return (false);
			if (!(*curr_tree))
				(*curr_tree) = new_branch;
			else if ((*curr_tree))
			{
				if (!(*curr_tree)->left_child)
				{
					(*curr_tree)->left_child = new_branch;
					new_branch->parent = (*curr_tree);
				}
			}
		}
		else
		{
			curr = last_par(curr->next);
			if (!building_tree(curr_tree, curr))
				return (false);
		}
	}
	return (true);
}

t_infopars	*last_par(t_infopars *lst_char)
{
	t_infopars	*curr;
	int			par;

	par = 0;
	curr = lst_char;
	while (curr->next)
	{
		if (curr->spe == 0)
		{
			if (curr->str[0] == '(')
				par++;
			else if (curr->str[0] == ')')
				par--;
		}
		if (par < 0)
			return (curr->prec);
		curr = curr->next;
	}
	return (curr);
}

t_infopars	*noeud_first(t_infopars *lst_char)
{
	t_infopars	*curr;
	int			par;

	curr = lst_char;
	par = 0;
	while (curr->prec)
	{
		if (curr->spe == 0)
		{
			if (curr->str[0] == '(')
				par--;
			else if (curr->str[0] == ')')
				par++;
		}
		if (curr->spe == 1 && par == 0)
			return (curr);
		else if (par < 0)
			return (curr->next);
		curr = curr->prec;
	}
	return (curr);
}
