/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:51:41 by yrio              #+#    #+#             */
/*   Updated: 2024/03/25 16:42:09 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	exec_child(char *cmd_path, char **cmd, t_shell *bash)
{
	int		result;

	result = execve(cmd_path, cmd, bash->env);
	if (result == -1)
		g_last_exit_code = 1;
	free_shell(bash);
	exit(127);
}

int	exec_cmdbash(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash)
{
	int	status;

	if (struct_cmd->child == 0)
	{
		if (struct_cmd->index == bash->len_cmds - 1)
			dup2(bash->std_out, 1);
		else
			dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		close(bash->std_out);
		if (is_builtins(struct_cmd->cmd))
			exec_builtins(struct_cmd->cmd, bash);
		else
			exec_child(cmd_path, struct_cmd->cmd, bash);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(struct_cmd->child, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
