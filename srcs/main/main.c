/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/02/20 10:52:31 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	launch_builtins(char **args_split, t_minishell *minishell)
{
	if (!ft_strcmp(args_split[0], "cd"))
		ft_cd(args_split, minishell);
	if (!ft_strcmp(args_split[0], "env"))
		ft_env(minishell);
	if (!ft_strcmp(args_split[0], "ls"))
		ls_cmd();
	if (!ft_strcmp(args_split[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(args_split[0], "export"))
		ft_export(args_split, minishell);
	if (!ft_strcmp(args_split[0], "unset"))
		ft_unset(args_split, minishell);
	if (!ft_strcmp(args_split[0], "echo"))
		ft_echo(args_split);
	if (!ft_strcmp(args_split[0], "exit"))
	{
		lstclear(minishell->lst_envs);
		ft_exit(args_split);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	char		**args_split;

	(void)argc;
	(void)argv;
	malloc_env(&minishell, env);
	rl_line_buffer = NULL;
	readline("minishell$ ");
	while (1)
	{
		args_split = ft_split(rl_line_buffer, ' ');
		if (args_split[0])
		{
			launch_builtins(args_split, &minishell);
			add_history(rl_line_buffer);
			free_split(args_split);
		}
		else
			free(args_split);
		readline("minishell$ ");
	}
	lstclear(minishell.lst_envs);
	return (0);
}
