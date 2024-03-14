/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:02 by yrio              #+#    #+#             */
/*   Updated: 2024/03/14 16:52:54 by yrio             ###   ########.fr       */
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

void	init_lstcmds(char **argv, t_shell *bash)
{
	t_lstcmd	*new;
	t_lstcmd	*lst;

	lst = init_cmd(argv[0], argv[1], 0);
	bash->lstcmd = lst;
	new = init_cmd(argv[3], argv[4], 1);
	lstcmdadd_back(new, lst);
	//printf("cmd 1 : |%s|, cmd 2 : |%s|\n", lst->cmd[0], lst->def_next->cmd[0]);
	//printf("arg 1 : |%s|, arg 2 : |%s|\n", lst->cmd[1], lst->def_next->cmd[1]);
}
