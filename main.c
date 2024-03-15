/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/15 16:50:10 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	pipe_loop(t_shell *bash)
{
	t_lstcmd	*cmds;
	char		*cmd_path;
	int			fd[2];
	int			std_out;

	cmds = bash->lstcmd;
	bash->len_cmds = lst_size(cmds);
	std_out = dup(1);
	while (cmds)
	{
		if (pipe(fd) == -1)
			break ;
		if (!is_builtins(cmds->cmd))
			cmd_path = check_cmd(cmds->cmd[0], bash->path);
		else
			cmd_path = NULL;
		cmds->child = fork();
		if (cmds->child == -1)
			free_shell(bash);
		exec_cmdbash(std_out, fd, cmd_path, cmds, bash);
		if (cmd_path)
			free(cmd_path);
		cmds = cmds->def_next;
	}
	free_shell(bash);
	close(std_out);
}

void	launch_execution(t_shell *bash)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		free_shell(bash);
	if (pid == 0)
	{
		pipe_loop(bash);
	}
	else
	{
		wait(NULL);
		free_shell(bash);
	}
}

int	main(int argc, const char **argv, const char **env)
{
	char	**args_split;
	t_shell	bash;

	if (argv == NULL)
		return (1);
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, env);
	bash.env = (char **)env;
	bash.path = get_paths((char **)env);
	args_split = ft_split(argv[1], ' ');
	init_lstcmds(args_split, &bash);
	launch_execution(&bash);
	free(args_split);
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
