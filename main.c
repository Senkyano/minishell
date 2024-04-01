/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/04/01 12:30:20 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	g_status_code;

void	pipe_loop(t_tree *tree, t_shell *bash)
{
	t_lstcmd	*cmds;
	char		*cmd_path;
	int			fd[2];

	g_status_code = IN_CMD;
	cmds = tree->lst_cmd;
	bash->len_cmds = lst_size(cmds);
	while (cmds)
	{
		if (pipe(fd) == -1)
			break ;
		if (!is_builtins(cmds->cmd))
		{
			cmd_path = check_cmd(cmds->cmd[0], bash->path);
			if (!cmd_path)
			{
				cmds->available = 0;
				cmds = cmds->def_next;
				close(fd[0]);
				close(fd[1]);
				continue ;
			}
		}
		else
			cmd_path = NULL;
		cmds->child = fork();
		if (cmds->child == -1)
			free_shell(bash);
		exec_cmdbash(fd, cmd_path, cmds, bash);
		if (cmd_path)
			free(cmd_path);
		cmds = cmds->def_next;
	}
}

int	wait_loop(t_tree *tree)
{
	t_lstcmd	*cmds;
	int 	status;
	int 	exit_status;

	cmds = tree->lst_cmd;
	while (cmds)
	{
		if (!lst_index(cmds, cmds->index)->available)
		{
			exit_status = 127;
			cmds = cmds->def_next;
			continue ;
		}
		waitpid(cmds->child, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		cmds = cmds->def_next;
	}
	g_status_code = 0;
	return (exit_status);
}

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
		if (!ft_strcmp(tree->lst_cmd->cmd[0], "exit") && !tree->lst_cmd->def_next)
			ft_exit(tree->lst_cmd->cmd, bash);
		pipe_loop(tree, bash);
		*exit_status = wait_loop(tree);
	}
	return (*exit_status);
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;
	char	*str;
	int	exit_status;

	if (argv == NULL)
		return (1);
	g_status_code = 0;
	init_signal();
	lib_memset(&bash, 0, sizeof(bash));
	bash.std_in = dup(0);
	bash.std_out = dup(1);
	malloc_env(&bash, (char **)env);
	bash.env = (char **)env;
	bash.path = get_paths((char **)env);
	exit_status = 0;
	rl_line_buffer = NULL;
	while (1)
	{
		str = readline(CY"Minishell >: "RST);
		add_history(str);
		if (!str)
		{
			close(bash.std_in);
			close(bash.std_out);
			free_shell(&bash);
			exit(0);
		}
		if (!ft_strcmp(str, "echo test && cat supp.supp && echvf evad || echo $? && echo test3 || echo ok"))
		{
			bash.str_split = ft_split(str, ' ');
			init_tree2(bash.str_split, &bash);
			exit_status = ft_tree_exec(bash.tree, &bash, &bash.env, &exit_status);
			dup2(bash.std_in, 0);
			free_tree(bash.tree);
			bash.tree = NULL;
		}
	}
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
