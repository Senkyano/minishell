/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/14 17:04:59 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	launch_builtins(char **cmd, t_shell *bash)
{
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, bash);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(bash);
	else if (!ft_strcmp(cmd[0], "ls"))
		ls_cmd();
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, bash);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, bash);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(bash);
	else
		return (0);
	return (1);
}

void	exec_cmdbash(int std_out, int *fd, t_lstcmd *struct_cmd, t_shell *bash, char **env)
{
	char	*cmd_path;
	int		len_cmds;
	pid_t	pid;

	cmd_path = check_cmd(struct_cmd->cmd[0], bash->path);
	len_cmds = lst_size(bash->lstcmd);
	pid = fork();
	if (pid == -1)
		free_shell(bash);
	if (pid == 0)
	{
		if (struct_cmd->index == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		if (struct_cmd->index == len_cmds - 1)
		{
			dup2(fd[0], 0);
			dup2(std_out, 1);
			close(fd[1]);
		}
		exec_child(cmd_path, struct_cmd->cmd, bash, env);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
	}
}

void	pipe_loop(t_shell *bash, char **env)
{
	t_lstcmd	*cmds;
	int			fd[2];
	int			std_out;

	cmds = bash->lstcmd;
	std_out = dup(1);
	while (cmds)
	{
		if (pipe(fd) == -1)
			break ;
		// if (is_builtins(cmds->cmd))
		// {
		// 	printf("cmd builtin : |%s|\n", cmds->cmd[0]);
		// 	dup2(fd[1], 1);
		// 	close(fd[1]);
		// 	close(fd[0]);
		// 	launch_builtins(cmds->cmd, bash);
		// 	dup2(fd[0], 0);
		// }
		// else
		// {
		exec_cmdbash(std_out, fd, cmds, bash, env);
		// }
		cmds = cmds->def_next;
	}
	free_shell(bash);
	close(std_out);
	exit(0);
}

void	launch_execution(t_shell *bash, char **env)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		free_shell(bash);
	if (pid == 0)
	{
		pipe_loop(bash, env);
	}
	else
		wait(NULL);
}

int	main(int argc, const char **argv, const char **env)
{
	char	**args_split;
	t_shell	bash;

	if (argv == NULL)
		return (1);
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, env);
	bash.path = get_paths((char **)env);
	args_split = ft_split(argv[1], ' ');
	init_lstcmds(args_split, &bash);
	pipe_loop(&bash, (char **)env);
	(void)argc;
	return (0);
}

// int	main(int argc, const char **argv, const char **env)
// {
// 	t_shell	bash;

// 	if (argv == NULL)
// 		return (1);
// 	lib_memset(&bash, 0, sizeof(bash));
// 	malloc_env(&bash, env);
// 	bash.path = get_paths((char **)env);
// 	launch_shell(argc, env);
// 	rl_line_buffer = NULL;
// 	readline(CY"Minishell >: "RST);
// 	while (1)
// 	{
// 		add_history(rl_line_buffer);
// 		if (valid_str(rl_line_buffer))
// 		{
// 			build_process(rl_line_buffer, &bash);
// 			launch_builtins(&bash);
// 			lib_free_split(bash.str_split);
// 		}
// 		else
// 			printf_error(RED"-- Feature not include --\n"RST);
// 		readline(CY"Minishell >: "RST);
// 	}
//	free_shell(&bash);
// 	return (0);
// }
