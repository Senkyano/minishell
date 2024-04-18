/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:19:54 by yrio              #+#    #+#             */
/*   Updated: 2024/04/18 18:08:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(char **cmd, t_shell *bash)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp(cmd[0], "cd"))
		exit_status = ft_cd(cmd, bash);
	else if (!ft_strcmp(cmd[0], "env" ))
		exit_status = ft_env(cmd, bash);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit_status = ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		exit_status = ft_export(cmd, bash);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, bash);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, bash);
	else
		return (0);
	free_shell(bash);
	exit(exit_status);
	return (1);
}

int	is_builtins(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	else
		return (0);
}

void	launch_builtins(int std_out, int *fd, t_lstcmd *cmds, t_shell *bash)
{
	dup2(fd[0], 0);
	if (cmds->index == 0)
		dup2(fd[1], 1);
	if (cmds->index == bash->len_cmds - 1)
		dup2(std_out, 1);
	close(fd[1]);
	close(fd[0]);
	exec_builtins(cmds->cmd, bash);
}

void	sigint_handler_here(int signal)
{
	if (signal == 2)
	{
		write(0, "\n", 1);
		exit(130);
	}
}
