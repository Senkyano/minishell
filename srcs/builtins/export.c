/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:45:08 by yrio              #+#    #+#             */
/*   Updated: 2024/04/18 15:40:32 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_export(char	**args_split, int index)
{
	char	**splitting_tmp;
	int		tmp;

	tmp = 0;
	splitting_tmp = ft_split_onedel(args_split[index], '=');
	if (check_empty_args(splitting_tmp))
		return (1);
	while (splitting_tmp[0][tmp])
	{
		if ((!((splitting_tmp[0][tmp] >= 48 && splitting_tmp[0][tmp] <= 57) || \
			(splitting_tmp[0][tmp] >= 65 && splitting_tmp[0][tmp] <= 90) || \
			(splitting_tmp[0][tmp] >= 97 && splitting_tmp[0][tmp] <= 122)) && \
			splitting_tmp[0][tmp] != '=' && splitting_tmp[0][tmp] != '_') ||
			args_split[index][0] == '=' || (splitting_tmp[0][0] >= 48 && \
			splitting_tmp[0][0] <= 57 && !ft_strchr(splitting_tmp[0], '=')))
		{
			printf("minishell: export: `%s': not a valid identifier\n", \
			args_split[index]);
			free_split(splitting_tmp);
			return (1);
		}
		tmp++;
	}
	free_split(splitting_tmp);
	return (0);
}

int	test_replace_elem(char **args_split, int tmp, t_shell *bash)
{
	t_envlist	*lst_envs;
	char		**splitting_tmp;

	lst_envs = bash->lst_envs;
	splitting_tmp = ft_split_onedel(args_split[tmp], '=');
	while (lst_envs)
	{
		if (!ft_strcmp(lst_envs->key, splitting_tmp[0]))
		{
			free_split(lst_envs->splitting);
			lst_envs->key = splitting_tmp[0];
			lst_envs->value = splitting_tmp[1];
			lst_envs->splitting = splitting_tmp;
			lst_envs->display = 1;
			return (1);
		}
		lst_envs = lst_envs->next;
	}
	free_split(splitting_tmp);
	return (0);
}

t_envlist	*add_elem_env(char **args_split, int tmp, t_shell *bash)
{
	t_envlist	*new;
	t_envlist	*lst_envs;

	lst_envs = bash->lst_envs;
	while (lst_envs->next)
		lst_envs = lst_envs->next;
	if (!ft_strchr(args_split[tmp], '='))
		new = lst_new(args_split[tmp], 0);
	else
		new = lst_new(args_split[tmp], 1);
	if (!new || (args_split[tmp][0] >= 48 && \
		args_split[tmp][0] <= 57))
	{
		printf("minishell: export: `%s': not a valid identifier\n", \
				args_split[tmp]);
		return (free_split(new->splitting), free(new), NULL);
	}
	lst_envs->next = new;
	return (new);
}

int	exec_export(char **args_split, int tmp, int exit_status, t_shell *bash)
{
	t_envlist	*new;

	if (!test_replace_elem(args_split, tmp, bash))
	{
		new = add_elem_env(args_split, tmp, bash);
		if (!new)
			exit_status = 1;
	}
	return (exit_status);
}

int	ft_export(char	**args_split, t_shell *bash)
{
	int			exit_status;
	int			tmp;

	if (!bash->lst_envs)
		return (0);
	if (!args_split[1])
		return (no_args(bash->lst_envs), 0);
	if (args_split[1][0] && args_split[1][0] == '-')
	{
		printf("bash: export: -%c: invalid option\n", args_split[1][1]);
		return (2);
	}
	tmp = 1;
	exit_status = 0;
	while (args_split[tmp])
	{
		if (parsing_export(args_split, tmp))
			exit_status = 1;
		else
			exit_status = exec_export(args_split, tmp, exit_status, bash);
		tmp++;
	}
	return (exit_status);
}
