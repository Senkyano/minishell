/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:03:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/09 20:59:53 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infopars	*last_par(t_infopars *lst_char);
t_infopars	*noeud_first(t_infopars *lst_char);
bool		more_process(t_infopars *lst_char);

bool	building_tree(t_tree **curr_tree, t_infopars *last_ele)
{
	t_infopars	*curr;
	t_tree		*new_branch;
	t_tree		*lst_cmd;

	if (last_ele->spe == 1) // si c'est un noeud on vas cree le noeud.
	{
		new_branch = build_branch(last_ele);
		if (!new_branch)
			return (false);
		if (!(*curr_tree))
			(*curr_tree) = new_branch;
		curr = noeud_first(last_ele->prec);
		if (!building_tree(&new_branch->left_child, curr))
			return (false);
		if (last_ele->next->spe != 0)
		{
			if (!building_tree(&new_branch->right_child, last_ele->next))
				return (false);
		}
		else if (last_ele->next->spe == 0)
		{
			curr = last_par(last_ele->next->next);
			curr = noeud_first(curr);
			printf_error("curr = %s\n", curr->str);
			if (!building_tree(&new_branch->right_child, curr))
				return (false);
		}
	}
	else if (last_ele->spe != 1)// si c'est pas un noeud alors on vas creer la liste de commande.
	{	// ca represente la partie tout a gauche la premiere liste en dehors des parentheses.
		if (last_ele->spe != 0) // si il n'y a pas de parenthese on fait le processus classique.
		{
			lst_cmd = build_branch(last_ele);
			if (!lst_cmd)
				return (false);
			(*curr_tree) = lst_cmd;
		}
		else if (last_ele->spe == 0 && last_ele->str[0] == '(') 
		{
			curr = last_par(last_ele->next);
			curr = noeud_first(curr);
			if (!building_tree(curr_tree, curr))
				return (false);
		}
	}
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
		if (curr->spe == 1 && par <= 0)
			return (true);
		curr = curr->prec;
	}
	return (false);
}

t_infopars	*last_par(t_infopars *lst_char)
{
	t_infopars	*curr;
	t_infopars	*last;
	int			par;

	par = 0;
	curr = lst_char;
	last = curr;
	while (curr)
	{
		if (curr->spe == 0)
		{
			if (curr->str[0] == '(')
				par++;
			else if (curr->str[0] == ')')
				par--;
		}
		if (curr->str[0] == ')' && par < 0)
			return (last);
		last = curr;
		curr = curr->next;
	}
	return (last);
}
