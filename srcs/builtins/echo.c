/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:44:32 by yrio              #+#    #+#             */
/*   Updated: 2024/04/18 13:15:57 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(int *first_arg, char **args_split)
{
	int	tmp;
	int	tmp2;

	tmp = 1;
	while (args_split[tmp] && !ft_strncmp(args_split[tmp], "-n", 2))
	{
		tmp2 = 2;
		while (args_split[tmp][tmp2] == 'n')
			tmp2++;
		if (args_split[tmp][tmp2] != '\0' && args_split[tmp][tmp2] != '\n')
			break ;
		tmp++;
	}
	*first_arg = tmp;
	if (tmp == 1)
		return (0);
	else
		return (1);
}

int	get_nb_args(char **args_split)
{
	int	tmp;
	int	nb_args;

	tmp = 1;
	nb_args = 0;
	if (args_split[tmp])
	{
		while (args_split[tmp])
		{
			nb_args++;
			tmp++;
		}
	}
	return (nb_args);
}

void	ft_echo(char **args_split)
{
	int	flag;
	int	first_arg;
	int	nb_args;

	first_arg = 1;
	flag = check_flag(&first_arg, args_split);
	nb_args = get_nb_args(args_split);
	if (!args_split[1])
		ft_putchar_fd('\n', 1);
	else if (!ft_strncmp(args_split[1], "-n", 2) && flag && !args_split[2])
		return ;
	else
	{
		while (first_arg <= nb_args)
		{
			ft_putstr_fd(args_split[first_arg], 1);
			first_arg++;
			if (first_arg <= nb_args)
				ft_putchar_fd(' ', 1);
		}
		if (!flag)
			ft_putchar_fd('\n', 1);
	}
}
