/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 07:26:19 by yrio              #+#    #+#             */
/*   Updated: 2024/03/25 17:05:30 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_exec.h"

int	check_env_key(t_shell *minishell, char *str)
{
	t_envlist	*lst;

	lst = minishell->lst_envs;
	while (lst)
	{
		if (!ft_strncmp(lst->key, str, ft_strlen(str)) && \
			(ft_strlen(lst->key) == ft_strlen(str)))
			return (1);
		lst = lst -> next;
	}
	return (0);
}

char	*get_value_env(t_shell *minishell, char *key)
{
	t_envlist	*lst;

	lst = minishell->lst_envs;
	while (lst)
	{
		if (!ft_strncmp(lst->key, key, ft_strlen(key)) && \
			(ft_strlen(lst->key) == ft_strlen(key)))
			return (lst->value);
		lst = lst -> next;
	}
	return (NULL);
}

int	ft_env(char **args_split, t_shell *minishell)
{
	t_envlist	*list_envs;
	int			tmp;
	
	if (!minishell->lst_envs)
	{
		ft_putstr_fd("bash: env: No such file or directory\n", 2);
		return (127);
	}
	tmp = 1;
	while (args_split[tmp])
	{
		if (ft_strcmp(args_split[tmp], "env"))
		{
			ft_printf("env: '%s': No such file or directory\n", args_split[tmp]);
			return (127);
		}
		tmp++;
	}
	list_envs = minishell->lst_envs;
	while (list_envs != NULL)
	{
		ft_putstr_fd(list_envs->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(list_envs->value, 1);
		ft_putchar_fd('\n', 1);
		list_envs = list_envs->next;
	}
	return (0);
}
