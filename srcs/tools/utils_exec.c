/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:51:41 by yrio              #+#    #+#             */
/*   Updated: 2024/04/02 11:47:03 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	exec_child(char *cmd_path, char **cmd, t_shell *bash)
{
	int		result;

	result = execve(cmd_path, cmd, bash->env);
	free_shell(bash);
	exit(127);
}

void	exec_cmd(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash)
{
	if (struct_cmd->child == 0)
	{
		init_signal_child();
		if (struct_cmd->index == bash->len_cmds - 1)
			dup2(bash->std_out, 1);
		else
			dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		close(bash->std_out);
		close(bash->std_in);
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
	}
}

void	ft_fork(int *fd, char *cmd_path, t_lstcmd *struct_cmd, t_shell *bash)
{
	struct_cmd->child = fork();
	if (struct_cmd->child == -1)
		free_shell(bash);
	exec_cmd(fd, cmd_path, struct_cmd, bash);
	if (cmd_path)
		free(cmd_path);
}

void	pipe_loop(t_tree *tree, t_shell *bash)
{
	t_lstcmd	*cmds;
	char		*cmd_path;
	int			fd[2];

	g_status_code = IN_CMD;
	cmd_path = NULL;
	cmds = tree->lst_cmd;
	bash->len_cmds = lst_size(cmds);
	while (cmds)
	{
		if (pipe(fd) == -1)
			break ;
		if (!is_builtins(cmds->cmd))
			cmd_path = check_cmd(cmds->cmd[0], bash->path);
		if (!is_builtins(cmds->cmd) && !cmd_path)
		{
			cmds->available = 0;
			close(fd[0]);
			close(fd[1]);
		}
		else
			ft_fork(fd, cmd_path, cmds, bash);
		cmds = cmds->def_next;
	}
}

int	wait_loop(t_tree *tree)
{
	t_lstcmd	*cmds;
	int			status;
	int			exit_status;

	cmds = tree->lst_cmd;
	while (cmds)
	{
		if (!lst_index(cmds, cmds->index)->available)
		{
			exit_status = 127;
			cmds = cmds->def_next;
			continue ;
		}
		waitpid(cmds->child, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		cmds = cmds->def_next;
	}
	g_status_code = 0;
	return (exit_status);
}
