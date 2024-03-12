/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:51:20 by yrio              #+#    #+#             */
/*   Updated: 2024/03/12 14:54:00 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_exec.h"

void	ft_unset(char **args_split, t_shell *minishell)
{
	t_envlist	*previous;
	t_envlist	*lst_envs;

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
			free_split(lst_envs->splitting);
			free(lst_envs);
			return ;	
		}
		previous = lst_envs;
		lst_envs = lst_envs->next;
	}
}
