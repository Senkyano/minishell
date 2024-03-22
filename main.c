/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/22 15:16:40 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_builtins(t_shell *bash)
{
	// if (!ft_strcmp(bash->str_split[0], "cd"))
	// 	ft_cd(bash->str_split, bash);
	// if (!ft_strcmp(bash->str_split[0], "env"))
	// 	ft_env(bash);
	// if (!ft_strcmp(bash->str_split[0], "ls"))
	// 	ls_cmd();
	// if (!ft_strcmp(bash->str_split[0], "pwd"))
	// 	ft_pwd();
	// if (!ft_strcmp(bash->str_split[0], "export"))
	// 	ft_export(bash->str_split, bash);
	// if (!ft_strcmp(bash->str_split[0], "unset"))
	// 	ft_unset(bash->str_split, bash);
	// if (!ft_strcmp(bash->str_split[0], "echo"))
	// 	ft_echo(bash->str_split);
	if (!ft_strcmp(bash->lst_char->str, "exit"))
	{
		// ft_exit(bash);
		free_shell(bash);
		exit(0);
	}
}

void	launch_execution(char **args_split, t_shell *bash)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		close_minishell(args_split, bash);
	if (pid == 0)
		close_minishell(args_split, bash);
	else
		wait(NULL);
	launch_builtins(bash);
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;

	if (argv == NULL)
		return (1);
	launch_shell(argc, env);
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, env);
	rl_line_buffer = NULL;
	while (1)
	{
		readline(CY"Minishell >: "RST);
		add_history(rl_line_buffer);
		if (build_process(rl_line_buffer, &bash))
		{
			printf_error(GR" Valid STR\n"RST);
			// printf_error(GR"ok\n"RST);
			launch_builtins(&bash);
		}
		free_boxshell(&bash.lst_char);
		// bash.exit_status = 0;
	}
	free_shell(&bash);
	return (0);
}
