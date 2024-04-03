/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/04/03 15:54:22 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

int	ft_tree_exec(t_tree *tree, t_shell *bash, char ***env, int *exit_status)
{
	if (tree->left_child)
		ft_tree_exec(tree->left_child, bash, env, exit_status);
	if (tree->type == OPERATOR_AND && *exit_status == 0)
		ft_tree_exec(tree->right_child, bash, env, exit_status);
	if (tree->type == OPERATOR_OR && *exit_status != 0)
		ft_tree_exec(tree->right_child, bash, env, exit_status);
	if (tree->type == LST_CMD)
	{
		if (!ft_strcmp(tree->lst_cmd->cmd[0], "exit") && \
			!tree->lst_cmd->next)
			ft_exit(tree->lst_cmd->cmd, bash);
		if (!ft_strcmp(tree->lst_cmd->cmd[0], "cd") && \
			!tree->lst_cmd->next)
		{
			ft_cd(tree->lst_cmd->cmd, bash);
			return (0);
		}
		pipe_loop(tree, bash);
		*exit_status = wait_loop(tree);
	}
	return (*exit_status);
}

t_shell	init_bash(char **env)
{
	t_shell	bash;

	lib_memset(&bash, 0, sizeof(bash));
	bash.std_in = dup(0);
	bash.std_out = dup(1);
	malloc_env(&bash, (char **)env);
	bash.env = (char **)env;
	bash.path = get_paths((char **)env);
	return (bash);
}

void	loop_minishell(int *exit_status, t_shell *bash)
{
	char	*str;

	while (1)
	{
		str = readline(CY"Minishell >: "RST);
		add_history(str);
		if (!str)
		{
			close(bash->std_in);
			close(bash->std_out);
			free_shell(bash);
			write(2, "exit\n", 6);
			exit(0);
		}
		else
		{
			if (!build_process(str, bash))
				continue ;
			// bash->str_split = ft_split(str, ' ');
			// init_tree2(bash->str_split, bash);
			init_signal_ign();
			bash->exit_status = ft_tree_exec(bash->tree, bash, \
				&bash->env, exit_status);
			init_signal();
			dup2(bash->std_in, 0);
			free_tree(bash->tree);
			bash->tree = NULL;
			g_status_code = 0;
		}
	}
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;
	int		exit_status;

	if (argv == NULL)
		return (1);
	g_status_code = 0;
	init_signal();
	bash = init_bash((char **)env);
	exit_status = 0;
	rl_line_buffer = NULL;
	loop_minishell(&exit_status, &bash);
	printf("exit_status : %d\n", exit_status);
	free_shell(&bash);
	(void)argc;
	return (0);
}

// int	main(int argc, const char **argv, const char **env)
// {
// 	t_shell	bash;
// 	int	exit_status;

// 	if (argv == NULL)
// 		return (1);
// 	g_last_exit_code = 0;
// 	lib_memset(&bash, 0, sizeof(bash));
// 	malloc_env(&bash, (char **)env);
// 	bash.env = (char **)env;
// 	bash.path = get_paths((char **)env);
// 	bash.str_split = ft_split(argv[1], ' ');
// 	init_tree(bash.str_split, &bash);
// 	exit_status = 0;
// 	exit_status = ft_tree_exec(bash.tree, &bash, &bash.env, &exit_status);
// 	printf("exit_status : %d\n", exit_status);
// 	free_shell(&bash);
// 	(void)argc;
// 	return (0);
// }

// int	main(int argc, const char **argv, const char **env)
// {
// 	t_shell	bash;
// 	char *str;

// 	if (argv == NULL)
// 		return (1);
// 	lib_memset(&bash, 0, sizeof(bash));
// 	//malloc_env(&bash, env);
// 	bash.path = get_paths((char **)env);
// 	launch_shell(argc, env);
// 	rl_line_buffer = NULL;
// 	readline(CY"Minishell >: "RST);
// 	while (1)
// 	{
// 		add_history(rl_line_buffer);
// 		// if (valid_str(rl_line_buffer))
// 		// {
// 		// 	//build_process(rl_line_buffer, &bash);
// 		// 	//launch_builtins(&bash);
// 		// 	//lib_free_split(bash.str_split);
// 		// }
// 		// else
// 		// 	printf_error(RED"-- Feature not include --\n"RST);
// 		str = readline(CY"Minishell >: "RST);
// 		printf("str : %s\n", str);
// 	}
// 	free_shell(&bash);
// 	return (0);
// }
