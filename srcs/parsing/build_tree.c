/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:29:42 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 12:40:32 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_tree(t_infopars *lst_char, int parenthese, t_tree *main_tree)
{
	t_infopars	*curr;
	t_tree		*curr_branch;

	curr = lst_char;
	if (exist_next_process(&curr))
	{
		if (curr->spe == 1)
			curr_branch = build_branch(curr);
		if (!main_tree)
			main_tree = curr_branch;
		else if (main_tree)
			main_tree->left_child = curr_branch;
	}
	else if (!exist_next_process(&curr))
	{
		if (curr->spe != 0)
			curr_branch = build_branch(curr);
	}
	if (curr->next->spe != 0 && curr->spe != 1)
	// faire le bloc de droit.
	return (curr_branch);
}

bool	exist_next_process(t_infopars **lst_char, int parenthese)
{
	while ((*lst_char)->prec)
	{
		if ((*lst_char)->spe == 1)
			return (true);
		(*lst_char) = (*lst_char)->prec;
	}
	return (false);
}
