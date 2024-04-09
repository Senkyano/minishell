/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:49:31 by yrio              #+#    #+#             */
/*   Updated: 2024/04/09 09:30:30 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_without_fork(t_tree *tree, t_shell *bash)
{
	if (!ft_strcmp(tree->lst_cmd->cmd[0], "exit") && \
		!tree->lst_cmd->next)
	{
		close(bash->std_in);
		close(bash->std_out);
		ft_exit(tree->lst_cmd->cmd, bash);
	}
	if (!ft_strcmp(tree->lst_cmd->cmd[0], "cd") && \
		!tree->lst_cmd->next)
	{
		ft_cd(tree->lst_cmd->cmd, bash);
		return (1);
	}
	else if (!ft_strcmp(tree->lst_cmd->cmd[0], "unset") && \
		!tree->lst_cmd->next)
	{
		ft_unset(tree->lst_cmd->cmd, bash);
		return (1);
	}
	else if (!ft_strcmp(tree->lst_cmd->cmd[0], "export") && \
		!tree->lst_cmd->next)
	{
		bash->exit_status = ft_export(tree->lst_cmd->cmd, bash);
		return (1);
	}
	return (0);
}
