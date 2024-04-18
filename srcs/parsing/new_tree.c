/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:03:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/18 18:48:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infopars	*last_par(t_infopars *lst_char);
bool		more_process(t_infopars *lst_char);
bool		branch_pro(t_tree **curr_tree, t_infopars *last_ele, t_shell *bash);
bool		branch_cmd(t_tree **curr_tree, t_infopars *last_ele, t_shell *bash);

bool	building_tree(t_tree **curr_tree, t_infopars *last_ele, t_shell *bash)
{
	if (last_ele->spe == 1)
	{
		if (bash->exit_status != 0)
			return (false);
		if (!branch_pro(curr_tree, last_ele, bash))
			return (false);
	}
	else if (last_ele->spe != 1)
	{
		if (bash->exit_status != 0)
			return (false);
		if (!branch_cmd(curr_tree, last_ele, bash))
			return (false);
	}
	return (true);
}

bool	branch_cmd(t_tree **curr_tree, t_infopars *last_ele, t_shell *bash)
{
	t_infopars	*curr;
	t_tree		*lst_cmd;

	if (last_ele->spe != 0)
	{
		lst_cmd = build_branch(last_ele, bash);
		if (!lst_cmd)
			return (false);
		(*curr_tree) = lst_cmd;
	}
	else if (last_ele->spe == 0 && last_ele->str[0] == '(')
	{
		curr = last_par(last_ele->next);
		curr = noeud_first(curr);
		if (!building_tree(curr_tree, curr, bash))
			return (false);
	}
	return (true);
}

bool	branch_pro(t_tree **curr_tree, t_infopars *last_ele, t_shell *bash)
{
	t_infopars	*curr;
	t_tree		*new_branch;

	new_branch = build_branch(last_ele, bash);
	if (!new_branch)
		return (false);
	if (!(*curr_tree))
		(*curr_tree) = new_branch;
	curr = noeud_first(last_ele->prec);
	if (!building_tree(&new_branch->left_child, curr, bash))
		return (false);
	if (last_ele->next->spe != 0)
	{
		if (!building_tree(&new_branch->right_child, last_ele->next, bash))
			return (false);
	}
	else if (last_ele->next->spe == 0)
	{
		curr = last_par(last_ele->next->next);
		curr = noeud_first(curr);
		if (!building_tree(&new_branch->right_child, curr, bash))
			return (false);
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
