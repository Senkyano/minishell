/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/13 14:39:27 by yrio             ###   ########.fr       */
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

void	launch_execution(t_shell *bash, char **env)
{
	char	*cmd_path;
	pid_t	pid;
	int		result;

	launch_builtins(bash);
	pid = fork();
	if (pid == -1)
		free_shell(bash);
	if (pid == 0)
	{
		cmd_path = check_cmd(bash->str_split[0], bash->path);
		result = execve(cmd_path, bash->str_split, env);
		if (result == -1)
			printf("Error execve\n");
		free_shell(bash);
		exit(0);
	}
	else
		wait(NULL);
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;

	if (argv == NULL)
		return (1);
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, env);
	bash.path = get_paths((char **)env);
	launch_shell(argc, env);
	rl_line_buffer = NULL;
	readline(CY"Minishell >: "RST);
	while (1)
	{
		add_history(rl_line_buffer);
		if (valid_str(rl_line_buffer))
		{
			build_process(rl_line_buffer, &bash);
			launch_execution(&bash, (char **)env);
			lib_free_split(bash.str_split);
		}
		else
			printf_error(RED"-- Feature not include --\n"RST);
		readline(CY"Minishell >: "RST);
	}
	free_shell(&bash);
	return (0);
}
