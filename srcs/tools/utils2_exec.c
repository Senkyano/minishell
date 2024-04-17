/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:49:31 by yrio              #+#    #+#             */
/*   Updated: 2024/04/17 11:55:25 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_env(t_tree *tree, t_shell *bash)
{
	if (!bash->lst_envs && !is_builtins(tree->lst_cmd->cmd))
	{
		bash->exit_status = 127;
		return (printf("bash: %s: No such file or directory\n", \
			tree->lst_cmd->cmd[0]));
	}
	return (0);
}

int	exec_without_fork(t_tree *tree, t_shell *bash)
{
	if (no_env(tree, bash))
		return (1);
	if (!ft_strcmp(tree->lst_cmd->cmd[0], "exit") && \
		!tree->lst_cmd->next)
	{
		close(bash->std_in);
		close(bash->std_out);
		return (ft_exit(tree->lst_cmd->cmd, bash), 1);
	}
	if (!ft_strcmp(tree->lst_cmd->cmd[0], "cd") && \
		!tree->lst_cmd->next)
		return (ft_cd(tree->lst_cmd->cmd, bash), 1);
	else if (!ft_strcmp(tree->lst_cmd->cmd[0], "unset") && \
		!tree->lst_cmd->next)
	{
		bash->exit_status = ft_unset(tree->lst_cmd->cmd, bash);
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
