/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:03:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/05 01:06:32 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*second_tree(t_infopars	*lstchar, t_tree *parent_branch, int parenthese)
{
	t_tree	*new_branch;
	t_tree	*tmp_branch;
	t_infopars	*curr;

	curr = lstchar;
	if (curr->spe == 1)
	{
		// pour creer un parent_branch.
	}
	else if (curr->spe != 1)
	{
		// pour creer les commandes.
	}
	return (parent_branch);
}

t_infopars	*check_point(t_infopars *lst_char, int parentheses)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr->prec)
	{
		if (curr->spe == 1)
			return (curr);
		curr = curr->prec;
	}
	return (curr);
}
