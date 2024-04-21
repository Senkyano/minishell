/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:49:31 by yrio              #+#    #+#             */
/*   Updated: 2024/04/21 13:33:15 by rihoy            ###   ########.fr       */
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
		return (ft_exit(tree->lst_cmd->cmd, bash), 1);
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

void	exec_cmd2(t_lstcmd *struct_cmd, t_shell *bash, char *cmd_path)
{
	if (is_builtins(struct_cmd->cmd))
		exec_builtins(struct_cmd->cmd, bash);
	else
		exec_child(cmd_path, struct_cmd->cmd, bash);
}

void	pipe_loop2(t_shell *bash, t_lstcmd *cmds, int *fd)
{
	char		*cmd_path;

	cmd_path = NULL;
	if (!is_builtins(cmds->cmd))
		cmd_path = check_cmd(cmds->cmd[0], bash->path);
	if ((!is_builtins(cmds->cmd) && !cmd_path))
	{
		cmds->available = 0;
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (strcmp(cmds->cmd[0], "cd"))
			cmd_path = ft_fork(fd, cmd_path, cmds, bash);
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
}
