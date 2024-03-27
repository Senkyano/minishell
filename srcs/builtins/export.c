/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:45:08 by yrio              #+#    #+#             */
/*   Updated: 2024/03/27 16:27:12 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	parsing_export(char	**args_split)
{
	int	tmp;

	tmp = 0;
	while (args_split[1][tmp])
	{
		if ((!((args_split[1][tmp] >= 48 && args_split[1][tmp] <= 57) || \
			(args_split[1][tmp] >= 65 && args_split[1][tmp] <= 90) || \
			(args_split[1][tmp] >= 97 && args_split[1][tmp] <= 122)) && \
			args_split[1][tmp] != '=') || args_split[1][0] == '=' || \
			(args_split[1][0] >= 48 && args_split[1][0] <= 57 && \
			!ft_strchr(args_split[1], '=')))
		{
			printf("minishell: export: `%s': not a valid identifier\n", \
			args_split[1]);
			return (0);
		}
		tmp++;
	}
	if (args_split[1] && !ft_strchr(args_split[1], '='))
		return (0);
	return (1);
}

void	no_args(t_envlist *lst_envs)
{
	while (lst_envs)
	{
		printf("declare -x %s=%s\n", lst_envs->key, lst_envs->value);
		lst_envs = lst_envs->next;
	}
}

int	ft_export(char	**args_split, t_shell *minishell)
{
	t_envlist	*lst_envs;
	t_envlist	*new;

	lst_envs = minishell->lst_envs;
	if (!args_split[1])
		return (no_args(lst_envs), 1);
	if (args_split[1][ft_strlen(args_split[1]) - 1] == '\n')
		args_split[1][ft_strlen(args_split[1]) - 1] = '\0';
	if (!parsing_export(args_split))
		return (1);
	while (lst_envs->next)
		lst_envs = lst_envs->next;
	new = lst_new(args_split[1]);
	if (!new || (args_split[1][0] >= 48 && \
		args_split[1][0] <= 57))
	{
		printf("minishell: export: `%s': not a valid identifier\n", \
			args_split[1]);
		return (free_split(new->splitting), free(new), 1);
	}
	lst_envs->next = new;
	return (0);
}
