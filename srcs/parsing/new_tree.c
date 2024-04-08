/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:03:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/08 22:20:50 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infopars	*last_par(t_infopars *lst_char);
t_infopars	*noeud_first(t_infopars *lst_char);
bool	more_process(t_infopars *lst_char);

bool	building_tree(t_tree **curr_tree, t_infopars *last_ele)
{
	t_infopars	*curr;
	t_tree		*new_branch;
	t_tree		*lst_cmd;

	curr = noeud_first(last_ele);
	// printf_error("first = %s\n", curr->str);
	// if (curr->spe != 0) // il ne faut pas que le debut et la fin soit des parenthses.
	// {
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
			if (more_process(curr))
				building_tree(&new_branch, curr->prec);
			if (curr->next->spe != 0) // construction de la liste de commande de droite.
			{
				lst_cmd = build_branch(curr->next);
				if (!lst_cmd)
					return (false);
				new_branch->right_child = lst_cmd;
				lst_cmd->parent = new_branch;
			}
			else // a refaire
			{
				curr = last_par(curr->next);
				// printf_error("curr par = %s\n", curr->str);
				if (!building_tree(&new_branch, curr->prec))
					return (false);
			}
		}
		else // si c'est pas un noeud alors on vas creer la liste de commande.
		{	// ca represente la partie tout a gauche la premiere liste en dehors des parentheses.
			if (curr->spe != 0) // si il n'y a pas de parenthese on fait le processus classique.
			{
				lst_cmd = build_branch(curr);
				if (!lst_cmd)
					return (false);
				if (!(*curr_tree))
					(*curr_tree) = lst_cmd;
				else if ((*curr_tree))
				{
					if (!(*curr_tree)->left_child)
					{
						(*curr_tree)->left_child = lst_cmd;
						lst_cmd->parent = (*curr_tree);
					}
					else
					{
						(*curr_tree)->right_child = lst_cmd;
						lst_cmd->parent = (*curr_tree);
					}
				}
			}
			else // si il y a une parenthse alors on doit refaire un nouveau processus de traitement.
			{ // a refaire
				curr = last_par(curr->next);
				printf_error("curr par = %s\n", curr->str);
				if (!building_tree(curr_tree, curr))
					return (false);
			}
		}
	// }
	// else
	return (true);
}

bool	more_process(t_infopars *lst_char)
{
	t_infopars	*curr;
	int			par;

	par = 0;
	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 0)
		{
			if (curr->str[0] == '(')
				par--;
			else if (curr->str[0] == ')')
				par++;
		}
		if (curr->spe == 1 && par == 0)
			return (true);
		curr = curr->prec;
	}
	return (false);
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
