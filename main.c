/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/13 11:44:38 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	launch_builtins(t_shell *bash)
{
	if (!ft_strcmp(bash->str_split[0], "cd"))
		ft_cd(bash->str_split, bash);
	if (!ft_strcmp(bash->str_split[0], "env"))
		ft_env(bash);
	if (!ft_strcmp(bash->str_split[0], "ls"))
		ls_cmd();
	if (!ft_strcmp(bash->str_split[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(bash->str_split[0], "export"))
		ft_export(bash->str_split, bash);
	if (!ft_strcmp(bash->str_split[0], "unset"))
		ft_unset(bash->str_split, bash);
	if (!ft_strcmp(bash->str_split[0], "echo"))
		ft_echo(bash->str_split);
	if (!ft_strcmp(bash->str_split[0], "exit"))
		ft_exit(bash);
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
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, env);
	launch_shell(argc, env);
	rl_line_buffer = NULL;
	readline(CY"Minishell >: "RST);
	while (1)
	{
		add_history(rl_line_buffer);
		if (valid_str(rl_line_buffer))
		{
			build_process(rl_line_buffer, &bash);
			launch_builtins(&bash);
			lib_free_split(bash.str_split);
		}
		else
			printf_error(RED"-- Feature not include --\n"RST);
		readline(CY"Minishell >: "RST);
	}
	free_shell(&bash);
	return (0);
}
