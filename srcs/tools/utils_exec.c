/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:51:41 by yrio              #+#    #+#             */
/*   Updated: 2024/03/15 12:05:29 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	exec_child(char *cmd_path, char **cmd, t_shell *bash)
{
	int		result;

	result = execve(cmd_path, cmd, bash->env);
	if (result == -1)
		printf("Error execve\n");
	free_shell(bash);
	exit(0);
}

void	exec_cmdbash(int std_out, int *fd, char *cmd_path, t_lstcmd *struct_cmd, \
					t_shell *bash)
{
	if (struct_cmd->child == 0)
	{
		if (struct_cmd->index == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			close(std_out);
		}
		if (struct_cmd->index == bash->len_cmds - 1)
		{
			dup2(std_out, 1);
			close(fd[1]);
			close(fd[0]);
			close(std_out);
		}
		exec_child(cmd_path, struct_cmd->cmd, bash);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
	}
}

