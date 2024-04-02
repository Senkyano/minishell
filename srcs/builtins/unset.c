/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:51:20 by yrio              #+#    #+#             */
/*   Updated: 2024/04/02 17:06:19 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_path(char **args_split, t_shell *minishell)
{
	int	test;

	test = 0;
	if (!ft_strcmp(args_split[1], "PATH"))
	{
		lstclear(minishell->lst_envs);
		test = 1;
	}
	return (test);	
}

void	ft_unset(char **args_split, t_shell *minishell)
{
	t_envlist	*previous;
	t_envlist	*lst_envs;

	if (check_unset_path(args_split, minishell))
		return ;
	previous = NULL;
	lst_envs = minishell->lst_envs;
	while (lst_envs)
	{
		if (!ft_strncmp(lst_envs->key, args_split[1], ft_strlen(lst_envs->key)) \
			&& (ft_strlen(args_split[1]) - 1 == ft_strlen(lst_envs->key) || \
			ft_strlen(args_split[1]) == ft_strlen(lst_envs->key)))
		{
			
			if (previous && !lst_envs->next)
				previous->next = NULL;
			else if (previous && lst_envs->next)
				previous->next = lst_envs->next;
			else if (!previous)
				minishell->lst_envs = lst_envs->next;
			lib_free_split(lst_envs->splitting);
			free(lst_envs);
			return ;	
		}
		previous = lst_envs;
		lst_envs = lst_envs->next;
	}
}
