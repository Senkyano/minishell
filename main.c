/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:00:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/26 16:44:40 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	g_last_exit_code;

int	pipe_loop(t_tree *tree, t_shell *bash)
{
	t_lstcmd	*cmds;
	char		*cmd_path;
	int			fd[2];
	int			exit_status;

	cmds = tree->lst_cmd;
	bash->len_cmds = lst_size(cmds);
	bash->std_out = dup(1);
	while (cmds)
	{
		if (pipe(fd) == -1)
			break ;
		if (!is_builtins(cmds->cmd))
		{
			cmd_path = check_cmd(cmds->cmd[0], bash->path);
			if (!cmd_path)
				return (127);
		}
		else
			cmd_path = NULL;
		cmds->child = fork();
		if (cmds->child == -1)
			free_shell(bash);
		exit_status = exec_cmdbash(fd, cmd_path, cmds, bash);
		if (cmd_path)
			free(cmd_path);
		if (exit_status == 1)
			break ;
		cmds = cmds->def_next;
	}
	close(bash->std_out);
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
		if (!ft_strcmp(tree->lst_cmd->cmd[0], "exit"))
			ft_exit(tree, bash);
		*exit_status = pipe_loop(tree, bash);
	}
	return (*exit_status);
}

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;
	int	exit_status;

	if (argv == NULL)
		return (1);
	g_last_exit_code = 0;
	lib_memset(&bash, 0, sizeof(bash));
	malloc_env(&bash, (char **)env);
	bash.env = (char **)env;
	bash.path = get_paths((char **)env);
	bash.str_split = ft_split(argv[1], ' ');
	init_tree(bash.str_split, &bash);
	exit_status = 0;
	exit_status = ft_tree_exec(bash.tree, &bash, &bash.env, &exit_status);
	printf("exit_status : %d\n", exit_status);
	free_shell(&bash);
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
