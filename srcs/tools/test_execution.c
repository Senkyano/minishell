/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:02 by yrio              #+#    #+#             */
/*   Updated: 2024/03/26 16:30:13 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

t_lstcmd	*init_cmd(char *cmd, char *arg, int index)
{
	t_lstcmd *new_cmd;
	char	**cmd_split;

	new_cmd = malloc(sizeof(t_lstcmd));
	cmd_split = malloc(3 * sizeof(char *));
	new_cmd->index = index;
	new_cmd->cmd = cmd_split;
	cmd_split[0] = cmd;
	cmd_split[1] = arg;
	cmd_split[2] = NULL;
	new_cmd->t_path = NULL;
	new_cmd->child = -1;
	new_cmd->lst_fd = NULL;
	new_cmd->def_next = NULL;
	new_cmd->and_next = NULL;
	new_cmd->or_next = NULL;
	return (new_cmd);
}

void	lstcmdadd_back(t_lstcmd *new, t_lstcmd *lst)
{
	t_lstcmd	*tmp;

	tmp = lst;
	while (tmp->def_next != NULL)
	{
		tmp = tmp->def_next;
	}
	tmp->def_next = new;
}

void	lstcmdadd_back_or(t_lstcmd *new, t_lstcmd *lst)
{
	t_lstcmd	*tmp;

	tmp = lst;
	while (tmp->or_next != NULL)
	{
		tmp = tmp->or_next;
	}
	tmp->or_next = new;
}

void	lstcmdadd_back_and(t_lstcmd *new, t_lstcmd *lst)
{
	t_lstcmd	*tmp;

	tmp = lst;
	while (tmp->and_next != NULL)
	{
		tmp = tmp->and_next;
	}
	tmp->and_next = new;
}

t_tree	*new_tree_elem(t_lstcmd *cmds, int op)
{
	t_tree	*new;
	new = malloc(sizeof(t_tree));
	if (op)
		new->type = op;
	else
		new->type = LST_CMD;
	new->parent = NULL;
	new->left_child = NULL;
	new->right_child = NULL;
	if (cmds)
		new->lst_cmd = cmds;
	else
		new->lst_cmd = NULL;
	return (new);
}

void	init_tree(char **argv, t_shell *bash)
{
	t_tree		*tree;
	t_tree		*new1;
	t_tree		*new2;
	t_tree		*new3;
	t_tree		*new4;
	t_tree		*new5;
	t_tree		*new6;
	t_tree		*new7;
	t_tree		*new8;
	t_tree		*new9;
	t_tree		*new10;
	t_lstcmd	*cmd1;
	t_lstcmd	*cmd2;
	t_lstcmd	*cmd3;
	t_lstcmd	*cmd4;
	t_lstcmd	*cmd5;
	t_lstcmd	*cmd6;

	cmd1 = init_cmd(argv[0], argv[1], 0);
	cmd2 = init_cmd(argv[3], argv[4], 0);
	cmd3 = init_cmd(argv[6], argv[7], 0);
	cmd4 = init_cmd(argv[9], argv[10], 0);
	cmd5 = init_cmd(argv[12], argv[13], 0);
	cmd6 = init_cmd(argv[15], argv[16], 0);
	tree = new_tree_elem(0, OPERATOR_AND);
	new1 = new_tree_elem(0, OPERATOR_OR);
	new2 = new_tree_elem(0, OPERATOR_OR);
	new3 = new_tree_elem(0, OPERATOR_AND);
	new4 = new_tree_elem(cmd1, 0);
	new5 = new_tree_elem(0, OPERATOR_AND);
	new6 = new_tree_elem(cmd2, 0);
	new7 = new_tree_elem(cmd3, 0);
	new8 = new_tree_elem(cmd4, 0);
	new9 = new_tree_elem(cmd5, 0);
	new10 = new_tree_elem(cmd6, 0);
	
	tree->left_child = new1;
	tree->right_child = new2;
	new1->left_child = new3;
	new1->right_child = new8;
	new2->left_child = new9;
	new2->right_child = new10;
	new3->left_child = new4;
	new3->right_child = new5;
	new5->left_child = new6;
	new5->right_child = new7;

	free(argv[2]);
	free(argv[5]);
	free(argv[8]);
	free(argv[11]);
	free(argv[14]);

	bash->tree = tree;

	// printf("operator type : %d - %d\n", tree->type, \
	// 	tree->left_child->type);
}



/*
Test 1 : ./minishell "cat supp.supp | bdz vs || echo test"
Initialisation : 
	lst = init_cmd(argv[0], argv[1], 0);
	new = init_cmd(argv[3], argv[4], 1);
	lstcmdadd_back(new, lst);
	new = init_cmd(argv[6], argv[7], 0);
	lstcmdadd_back_or(new, lst);
	free(argv[2]);
	free(argv[5]);

Test 2 : ./minishell "ersgb ebs || echo test | wc -l"
Initialisation : 
	lst = init_cmd(argv[0], argv[1], 0);
	new = init_cmd(argv[3], argv[4], 0);
	lstcmdadd_back_or(new, lst);
	new = init_cmd(argv[6], argv[7], 1);
	lstcmdadd_back(new, lst->or_next);
	free(argv[2]);
	free(argv[5]);

Test 3 : ./minishell "ersgb ebs || ewdf test || cat supp.supp"
Initialisation :
	lst = init_cmd(argv[0], argv[1], 0);
	new = init_cmd(argv[3], argv[4], 0);
	lstcmdadd_back_or(new, lst);
	new = init_cmd(argv[6], argv[7], 0);
	lstcmdadd_back_or(new, lst);
	free(argv[2]);
	free(argv[5]);

Test 4 : ./minishell "cat supp.supp | wc -l | wc -l"
	t_lstcmd	*lst;
	t_lstcmd	*new;
	t_tree		*tree;

	lst = init_cmd(argv[0], argv[1], 0);
	new = init_cmd(argv[3], argv[4], 1);
	lstcmdadd_back(new, lst);
	new = init_cmd(argv[6], argv[7], 2);
	lstcmdadd_back(new, lst);
	free(argv[2]);
	free(argv[5]);
	tree = new_tree_elem(lst, 0);
	bash->tree = tree;

Test 5 : ./minishell "lSDZXs -a || cat supp.supp | wc -l  && echo ok
	t_tree		*tree;
	t_tree		*new1;
	t_tree		*new2;
	t_tree		*new3;
	t_tree		*new4;
	t_lstcmd	*cmd1;
	t_lstcmd	*cmd2;
	t_lstcmd	*cmd3;
	t_lstcmd	*cmd4;

	cmd1 = init_cmd(argv[0], argv[1], 0);
	cmd2 = init_cmd(argv[3], argv[4], 0);
	cmd3 = init_cmd(argv[6], argv[7], 1);
	lstcmdadd_back(cmd3, cmd2);
	cmd4 = init_cmd(argv[9], argv[10], 0);
	tree = new_tree_elem(0, OPERATOR_AND);
	new1 = new_tree_elem(0, OPERATOR_OR);
	new2 = new_tree_elem(cmd1, 0);
	new3 = new_tree_elem(cmd2, 0);
	new4 = new_tree_elem(cmd4, 0);
	
	tree->left_child = new1;
	tree->right_child = new4;
	new1->left_child = new2;
	new1->right_child = new3;

	bash->tree = tree;

Test 6 : ./minishell "echo test && cat supp.supp && echvf evad || echo $? && echo test3 || echo ok"
cdm : echo test && (cat supp.supp && echvf evad) || echo $? && ((echo test3) || echo ok)

	t_tree		*tree;
	t_tree		*new1;
	t_tree		*new2;
	t_tree		*new3;
	t_tree		*new4;
	t_tree		*new5;
	t_tree		*new6;
	t_tree		*new7;
	t_tree		*new8;
	t_tree		*new9;
	t_tree		*new10;
	t_lstcmd	*cmd1;
	t_lstcmd	*cmd2;
	t_lstcmd	*cmd3;
	t_lstcmd	*cmd4;
	t_lstcmd	*cmd5;
	t_lstcmd	*cmd6;

	cmd1 = init_cmd(argv[0], argv[1], 0);
	cmd2 = init_cmd(argv[3], argv[4], 0);
	cmd3 = init_cmd(argv[6], argv[7], 0);
	cmd4 = init_cmd(argv[9], argv[10], 0);
	cmd5 = init_cmd(argv[12], argv[13], 0);
	cmd6 = init_cmd(argv[15], argv[16], 0);
	tree = new_tree_elem(0, OPERATOR_AND);
	new1 = new_tree_elem(0, OPERATOR_OR);
	new2 = new_tree_elem(0, OPERATOR_OR);
	new3 = new_tree_elem(0, OPERATOR_AND);
	new4 = new_tree_elem(cmd1, 0);
	new5 = new_tree_elem(0, OPERATOR_AND);
	new6 = new_tree_elem(cmd2, 0);
	new7 = new_tree_elem(cmd3, 0);
	new8 = new_tree_elem(cmd4, 0);
	new9 = new_tree_elem(cmd5, 0);
	new10 = new_tree_elem(cmd6, 0);
	
	tree->left_child = new1;
	tree->right_child = new2;
	new1->left_child = new3;
	new1->right_child = new8;
	new2->left_child = new9;
	new2->right_child = new10;
	new3->left_child = new4;
	new3->right_child = new5;
	new5->left_child = new6;
	new5->right_child = new7;

	free(argv[2]);
	free(argv[5]);
	free(argv[8]);
	free(argv[11]);
	free(argv[14]);

	bash->tree = tree;

Test 7 : ./minishell "cat supp.supp"
	t_tree		*tree;
	t_lstcmd	*cmd1;

	cmd1 = init_cmd(argv[0], argv[1], 0);
	tree = new_tree_elem(cmd1, 0);

	bash->tree = tree;
*/


void	free_lstcmds(t_shell *bash)
{
	int			tmp;
	t_lstcmd	*lst;
	t_lstcmd	*old;

	lst = bash->lstcmd;
	while (lst)
	{
		tmp = 0;
		old = lst;
		free_split(lst->cmd);
		lst = lst->def_next;
		free(old);
	}
}
