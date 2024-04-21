/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:51:41 by yrio              #+#    #+#             */
/*   Updated: 2024/04/21 13:33:52 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(char *cmd_path, char **cmd, t_shell *bash)
{
	init_signal_child();
	if ((check_env_key(bash, "PATH") && check_path(bash)) || \
		access(cmd[0], F_OK) == 0)
		execve(cmd_path, cmd, bash->env);
	else
		printf_error("bash: %s: No such file or directory\n", cmd[0]);
	free(cmd_path);
	free_shell(bash);
	exit(127);
}

void	exec_cmd(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash)
{
	if (struct_cmd->child == 0)
	{
		if (struct_cmd->out_file > 0)
			dup2(struct_cmd->out_file, 1);
		else
		{
			if (struct_cmd->index == bash->len_cmds - 1)
				dup2(bash->std_out, 1);
			else
				dup2(fd[1], 1);
		}
		close_tree(bash->tree);
		close(fd[1]);
		close(fd[0]);
		close(bash->std_out);
		close(bash->std_in);
		exec_cmd2(struct_cmd, bash, cmd_path);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
	}
}

char	*ft_fork(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash)
{
	struct_cmd->child = fork();
	if (struct_cmd->child == -1)
		free_shell(bash);
	exec_cmd(fd, cmd_path, struct_cmd, bash);
	if (cmd_path)
	{
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}

void	pipe_loop(t_tree *tree, t_shell *bash)
{
	t_lstcmd	*cmds;
	int			fd[2];

	cmds = tree->lst_cmd;
	bash->len_cmds = lst_size(cmds);
	while (cmds)
	{
		if (cmds->in_file > 0)
			dup2(cmds->in_file, 0);
		if (pipe(fd) == -1 || cmds->in_file == -1)
			break ;
		pipe_loop2(bash, cmds, fd);
		cmds = cmds->next;
	}
	if (cmds)
	{
		if (fd[0] > 0)
			close(fd[0]);
		if (fd[1] > 0)
			close(fd[1]);
	}
}

int	wait_loop(t_tree *tree, t_shell *bash)
{
	t_lstcmd	*cmds;
	int			status;

	status = -1;
	cmds = tree->lst_cmd;
	while (cmds)
	{
		if (cmds->cmd[0] && !lst_index(cmds, cmds->index)->available)
		{
			if (cmds->cmd[0][0] == '.' && cmds->cmd[0][1] == '/' && \
				access(cmds->cmd[0], X_OK) == -1)
				bash->exit_status = 126;
			else
				bash->exit_status = 127;
			cmds = cmds->next;
			continue ;
		}
		waitpid(cmds->child, &status, 0);
		if (WIFEXITED(status))
			bash->exit_status = WEXITSTATUS(status);
		bash->exit_status = manage_signal(status, bash->exit_status);
		cmds = cmds->next;
	}
	return (bash->exit_status);
}
