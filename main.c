/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/04/22 13:55:38 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_code;

int	ft_tree_exec(t_tree *tree, t_shell *bash, char ***env)
{
	if (tree->left_child)
		ft_tree_exec(tree->left_child, bash, env);
	if (tree->type == OPERATOR_AND && bash->exit_status == 0)
		ft_tree_exec(tree->right_child, bash, env);
	if (tree->type == OPERATOR_OR && bash->exit_status != 0)
		ft_tree_exec(tree->right_child, bash, env);
	if (tree->type == LST_CMD)
	{
		if (exec_without_fork(tree, bash))
			return (bash->exit_status);
		else
		{
			pipe_loop(tree, bash);
			bash->exit_status = wait_loop(tree, bash);
			dup2(bash->std_in, 0);
		}
	}
	return (bash->exit_status);
}

t_shell	init_bash(char **env)
{
	t_shell	bash;

	lib_memset(&bash, 0, sizeof(bash));
	bash.std_in = dup(0);
	bash.std_out = dup(1);
	if (!bash.std_in || !bash.std_out)
		exit(0);
	malloc_env(&bash, (char **)env);
	bash.env = (char **)env;
	bash.len_cmds = 0;
	bash.path = get_paths((char **)env);
	if (!bash.path)
		exit(127);
	return (bash);
}

void	post_init_exec(t_shell *bash)
{
	init_signal();
	dup2(bash->std_in, 0);
	free_tree(bash->tree);
	bash->tree = NULL;
	bash->len_cmds = 0;
	g_status_code = 0;
}

void	loop_minishell(t_shell *bash)
{
	char	*str;

	while (1)
	{
		str = readline(CY"Minishell >: "RST);
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
			bash->last_exit_status = bash->exit_status;
			bash->exit_status = 0;
			if (!build_process(str, bash))
				continue ;
			init_signal_ign();
			bash->exit_status = ft_tree_exec(bash->tree, bash, &bash->env);
			post_init_exec(bash);
		}
	}
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;

	launch_shell(argc, env);
	if (argv == NULL)
		return (1);
	g_status_code = 0;
	init_signal();
	bash = init_bash((char **)env);
	bash.exit_status = 0;
	rl_line_buffer = NULL;
	loop_minishell(&bash);
	(void)argc;
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (argc == 2)
// 		i = len_inquote(argv[1]);
// 	printf_error("i = %d\n", i);
// 	return (0);
// }

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
