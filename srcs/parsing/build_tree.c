/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:29:42 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 16:46:04 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exist_next_process(t_infopars **lst_char, int parenthese);

bool	build_tree(t_infopars *lst_char, int parenthese, t_tree **main_tree)
{
	t_infopars	*curr;
	t_tree		*curr_branch;
	t_tree		*curr_tmp;

	curr = lst_char;
	if (exist_next_process(&curr, parenthese))
	{
		curr_branch = build_branch(curr);
		if (!(*main_tree))
			(*main_tree) = curr_branch;
		else if ((*main_tree))
		{
			(*main_tree)->left_child = curr_branch;
			curr_branch->parent = (*main_tree);
		}
		if (!build_tree(curr->prec, 0, &curr_branch))
			return (false);
		if (curr->next->spe != 0 && curr->next->spe != 1)
		{
			curr_tmp = build_branch(curr->next);
			if (!curr_tmp)
				return (false);
			curr_branch->right_child = curr_tmp;
			curr_tmp->parent = curr_branch;
		}
	}
	else if (!exist_next_process(&curr, parenthese))
	{
		if (curr->spe != 0)
		{
			curr_tmp = build_branch(curr);
			if (!curr_tmp)
				return (false);
		}
		if (!(*main_tree))
			(*main_tree) = curr_tmp;
		else if ((*main_tree) && !(*main_tree)->left_child)
		{
			(*main_tree)->left_child = curr_tmp;
			curr_tmp->parent = (*main_tree);
		}
		return (true);
	}
	return (true);
}

void	free_tree(t_tree *main_tree)
{
	if (main_tree->left_child)
		free_tree(main_tree->left_child);
	if (main_tree->right_child)
		free_tree(main_tree->right_child);
	free_branch(main_tree);
}

void	print_tree(t_tree *main_tree)
{
	if (main_tree->left_child)
		print_tree(main_tree->left_child);
	if (main_tree->right_child)
		print_tree(main_tree->right_child);
	if (main_tree->lst_cmd)
		print_lstcmd(main_tree->lst_cmd);
}

bool	exist_next_process(t_infopars **lst_char, int parenthese)
{
	int	count_par;

	count_par = parenthese;
	while ((*lst_char)->prec && count_par >= parenthese)
	{
		if ((*lst_char)->spe == 0 && (*lst_char)->str[0] == ')')
			count_par++;
		else if ((*lst_char)->spe == 0 && (*lst_char)->str[0] == '(')
			count_par--;
		if ((*lst_char)->spe == 1 && count_par == parenthese)
			return (true);
		(*lst_char) = (*lst_char)->prec;
	}
	return (false);
}
