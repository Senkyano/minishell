/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:29:42 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/07 19:26:22 by rihoy            ###   ########.fr       */
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
	if (exist_next_process(curr, parenthese)) // cherche si il y a un noeud dans la commande
	{
		curr = go_to_process(curr, parenthese); // direction le noeud dans la commande
		curr_branch = build_branch(curr); // construire le noeud.
		if (!curr_branch) // si la curr_branch n'a pas pus etre construite
			return (NULL);
		if (!(*main_tree)) // definir si le main_tree est vide ou pas
			(*main_tree) = curr_branch;
		else if ((*main_tree))
		{
			(*main_tree)->left_child = curr_branch;
			curr_branch->parent = (*main_tree);
		}
		if (!build_tree(curr->prec, parenthese, &curr_branch)) // comme on sait que apres le noeud il y a forcement un commande.
			return (NULL);
		if (curr->next->spe != 0)
			curr_tmp = build_branch(curr->next); // construction de la liste de commande.
		else if (curr->next->spe == 0) // si il y a une parenthese apres le noeud.
			curr_tmp = NULL;
		if (!curr_tmp) // protection
			return (NULL);
		curr_branch->right_child = curr_tmp; // on met dans le noeud de droite.
		curr_tmp->parent = curr_branch; // on relie la nouvelle branche a son parent.
	}
	else if (!exist_next_process(curr, parenthese)) // cherche si il y a un noeud dans la commande
	{
		curr = go_to_process(curr, parenthese); // direction aux dernier ou le premier element.
		if (curr->spe != 0)
			curr_tmp = build_branch(curr); // construction de la liste de commande.
		else if (curr->spe == 0) // si il y a une parenthese aux debut de la commande.
			curr_tmp = NULL;
		if (!curr_tmp) // protection
			return (NULL);
		if (!(*main_tree)) // rattache la liste de commande aux noeud dans la branche de gauche.
			(*main_tree) = curr_tmp; // soit elle existe pas et on la place.
		else if ((*main_tree) && !(*main_tree)->left_child)
		{
			(*main_tree)->left_child = curr_tmp;
			curr_tmp->parent = (*main_tree);
		}
		return (curr_tmp);
	}
	return ((*main_tree)); // on retourne le main qui seras le noeud principale de la structure.
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
