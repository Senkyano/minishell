/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:02 by yrio              #+#    #+#             */
/*   Updated: 2024/03/18 16:13:13 by yrio             ###   ########.fr       */
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

void	init_lstcmds(char **argv, t_shell *bash)
{
	t_lstcmd	*new;
	t_lstcmd	*lst;

	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 1); // quand c'est avec un "ou" il faut remettre
	// l'index a 0 pour la premiere commande de l'autre processus
	lstcmdadd_back(new, lst);
	new = init_cmd(argv[6], argv[7], 2);
	lstcmdadd_back(new, lst); // lorsqu'on ajoute un pipe entre deux
	// element, mais qu'il y a eu un "ou" avant, il faut avancer a l'element 
	// "or_next" suivant
	// quand il y a un "ou" dans le 2e processus on le met le "or_next" sur 
	// le premier element du premier processus
	free(argv[2]);
	free(argv[5]);
	// printf("cmd 1 : |%s|, cmd 2 : |%s|\n", lst->cmd[0], lst->or_next->cmd[0]);
	// printf("arg 1 : |%s|, arg 2 : |%s|\n", lst->cmd[1], lst->or_next->cmd[1]);
}

/*
Test 1 : ./minishell "cat supp.supp | bdz vs || echo test"
Initialisation : 
	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 1);
	lstcmdadd_back(new, lst);
	new = init_cmd(argv[6], argv[7], 0);
	lstcmdadd_back_or(new, lst);
	free(argv[2]);
	free(argv[5]);

Test 2 : ./minishell "ersgb ebs || echo test | wc -l"
Initialisation : 
	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 0);
	lstcmdadd_back_or(new, lst);
	new = init_cmd(argv[6], argv[7], 1);
	lstcmdadd_back(new, lst->or_next);
	free(argv[2]);
	free(argv[5]);

Test 3 : ./minishell "ersgb ebs || ewdf test || cat supp.supp"
Initialisation :
	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 0);
	lstcmdadd_back_or(new, lst);
	new = init_cmd(argv[6], argv[7], 0);
	lstcmdadd_back_or(new, lst);
	free(argv[2]);
	free(argv[5]);

Test 4 : ./minishell "cat supp.supp | wc -l | wc -l"
	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 1);
	lstcmdadd_back(new, lst);
	new = init_cmd(argv[6], argv[7], 2);
	lstcmdadd_back(new, lst);
	free(argv[2]);
	free(argv[5]);
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
