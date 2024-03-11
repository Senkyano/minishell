/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/02/21 13:26:42 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_minishell_standard(char **argv, t_minishell *minishell)
{
	//minishell->total_cmd = argc - 3;
	minishell->infile_name = argv[1];
	//minishell->outfile_name = argv[argc - 1];
	minishell->recup = -1;
	minishell->fd_infile = open(minishell->infile_name, O_RDONLY, 0644);
	minishell->fd_outfile = open(minishell->outfile_name, O_CREAT | \
		O_RDWR | O_TRUNC, 0644);
	if (minishell->fd_infile == -1 || minishell->fd_outfile == -1)
		minishell->error_init = 1;
}

void	init_cmdline(char **args_split, t_minishell *minishell)
{
	t_envlist	*envlist;
	t_cmdline	*elem;
	t_cmdline	*new;
	int			*pid;
	int			tmp;

	envlist = minishell->lst_envs;
	minishell->error_init = 0;
	tmp = 0;
	elem = new_elem_cmdline(tmp, args_split, minishell);
	minishell->lst_envs = elem;
	tmp++;
	while (tmp < minishell->total_cmd)
	{
		new = new_elem_cmdline(tmp, args_split, minishell);
		lstadd_back(new, elem);
		tmp++;
	}
	pid = malloc((minishell->total_cmd) * sizeof(int));
	minishell->pid = pid;
	if (!minishell->pid)
		minishell->error_init = 1;
}

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
		init_cmdline(args_split, &minishell);
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
