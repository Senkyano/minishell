/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:51:20 by yrio              #+#    #+#             */
/*   Updated: 2024/04/17 11:20:13 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_path(char **args_split, t_shell *bash)
{
	int	test;

	test = 0;
	if (!ft_strcmp(args_split[1], "PATH"))
	{
		lstclear(bash->lst_envs);
		bash->lst_envs = NULL;
		test = 1;
	}
	return (test);
}

int	parsing_unset(char **args_split)
{
	int	tmp;

	if ((args_split[1] && !ft_strlen(args_split[1])) || (args_split[1][0] >= 48 \
		&& args_split[1][0] <= 57))
	{
		printf("bash: unset: %s: not a valid identifier\n", args_split[1]);
		return (1);
	}
	tmp = 0;
	while (args_split[1][tmp])
	{
		if ((!((args_split[1][tmp] >= 48 && args_split[1][tmp] <= 57) || \
			(args_split[1][tmp] >= 65 && args_split[1][tmp] <= 90) || \
			(args_split[1][tmp] >= 97 && args_split[1][tmp] <= 122)) && \
			args_split[1][tmp] != '_') || args_split[1][0] == '=')
		{
			printf("bash: export: `%s': not a valid identifier\n", \
			args_split[1]);
			return (1);
		}
		tmp++;
	}
	return (0);
}

void	exec_unset(t_envlist *previous, t_envlist *lst_envs, t_shell *bash)
{
	if (previous && !lst_envs->next)
		previous->next = NULL;
	else if (previous && lst_envs->next)
		previous->next = lst_envs->next;
	else if (!previous)
		bash->lst_envs = lst_envs->next;
	lib_free_split(lst_envs->splitting);
	free(lst_envs);
}

int	ft_unset(char **args_split, t_shell *bash)
{
	t_envlist	*previous;
	t_envlist	*lst_envs;

	if (!args_split[1])
		return (0);
	if (args_split[1][0] && args_split[1][0] == '-')
	{
		printf("bash: unset: -%c: invalid option\n", args_split[1][1]);
		return (2);
	}
	if (parsing_unset(args_split))
		return (1);
	previous = NULL;
	lst_envs = bash->lst_envs;
	while (lst_envs)
	{
		if (!ft_strncmp(lst_envs->key, args_split[1], ft_strlen(lst_envs->key)) \
			&& ft_strlen(args_split[1]) == ft_strlen(lst_envs->key))
			return (exec_unset(previous, lst_envs, bash), 0);
		previous = lst_envs;
		lst_envs = lst_envs->next;
	}
	return (0);
}
