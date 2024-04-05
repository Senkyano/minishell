/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:29:42 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/05 19:24:10 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exist_next_process(t_infopars *lst_char, int parenthese);
t_infopars	*go_to_process(t_infopars *lst_char, int parentheses);
t_infopars	*go_last_par(t_infopars *lst_char, int parenthese);

t_tree	*build_tree(t_infopars *lst_char, int parenthese, t_tree **main_tree)
{
	t_infopars	*curr;
	t_tree		*curr_branch;
	t_tree		*curr_tmp;

	curr = lst_char;
	curr_tmp = NULL;
	curr_branch = NULL;
	printf_error("%d\n", parenthese);
	if (parenthese == 2)
		return (NULL);
	if (exist_next_process(curr, parenthese)) // refaire pour qu'il prend en compte les parenthese
	{
		curr = go_to_process(curr, parenthese);
		printf_error("%s\n", curr->str);
		curr_branch = build_branch(curr);
		if (!(*main_tree))
			(*main_tree) = curr_branch;
		else if ((*main_tree))
		{
			(*main_tree)->left_child = curr_branch;
			curr_branch->parent = (*main_tree);
		}
		if (!build_tree(curr->prec, parenthese, &curr_branch))
			return (NULL);
		if (curr->next->spe == 0)
		{
			printf_error("%s\n", curr->next->str);
			curr = go_last_par(curr, parenthese + 1);
			printf_error("%s\n", curr->str);
			// curr_tmp = build_tree(curr->prec, parenthese + 1, &curr_branch);
		}
		else if (curr->next->spe != 0 && curr->next->spe != 1)
			curr_tmp = build_branch(curr->next);
		if (!curr_tmp)
			return (NULL);
		curr_branch->right_child = curr_tmp;
		if (curr_tmp != NULL)
			curr_tmp->parent = curr_branch;
	}
	else if (!exist_next_process(curr, parenthese)) // refaire pour qu'il prend en compte les parenthese
	{
		curr = go_to_process(curr, parenthese);
		printf_error("%s\n", curr->str);
		if (curr->spe == 0)
		{
			printf_error("%s\n", curr->str);
			curr = go_last_par(curr, parenthese + 1);
			printf_error("%s\n", curr->str);
			// curr_tmp = build_tree(curr->prec, parenthese + 1, main_tree);
		}
		else if (curr->spe != 0)
			curr_tmp = build_branch(curr);
		if (!curr_tmp)
			return (NULL);
		if (!(*main_tree))
			(*main_tree) = curr_tmp;
		else if ((*main_tree) && !(*main_tree)->left_child)
		{
			(*main_tree)->left_child = curr_tmp;
			curr_tmp->parent = (*main_tree);
		}
		return (curr_tmp);
	}
	return ((*main_tree));
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

t_infopars	*go_last_par(t_infopars *lst_char, int parenthese)
{
	int	count_par;

	count_par = parenthese;
	while (lst_char->next && count_par > parenthese - 1)
	{
		if (lst_char->spe == 0 && lst_char->str[0] == ')')
			count_par--;
		else if (lst_char->spe == 0 && lst_char->str[0] == '(')
			count_par++;
		lst_char = lst_char->next;
	}
	return (lst_char);
}

t_infopars	*go_to_process(t_infopars *lst_char, int parentheses)
{
	int	count_par;

	count_par = parentheses;
	while (lst_char->prec && count_par > parentheses - 1)
	{
		if (lst_char->spe == 0 && lst_char->str[0] == ')')
			count_par++;
		else if (lst_char->spe == 0 && lst_char->str[0] == '(')
			count_par--;
		if (lst_char->spe == 1 && count_par == parentheses)
			return (lst_char);
		lst_char = lst_char->prec;
	}
	return (lst_char);
}

bool	exist_next_process(t_infopars *lst_char, int parenthese)
{
	int	count_par;

	count_par = parenthese;
	while (lst_char->prec && count_par > parenthese - 1)
	{
		if (lst_char->spe == 0 && lst_char->str[0] == ')')
			count_par++;
		else if (lst_char->spe == 0 && lst_char->str[0] == '(')
			count_par--;
		if (lst_char->spe == 1 && count_par == parenthese)
			return (true);
		lst_char = lst_char->prec;
	}
	return (false);
}
