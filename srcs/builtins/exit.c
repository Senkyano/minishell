/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:45:55 by yrio              #+#    #+#             */
/*   Updated: 2024/03/25 14:30:48 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	check_out_of_range(unsigned long long value, int *error, int neg)
{
	if (value > LONG_MAX && neg == 1)
		*error = 1;
	else if (neg == -1 && value > (unsigned long long)9223372036854775807 + 1)
		*error = 1;
	return (*error);
}

long int	ft_atoi_long(const char *str, int *error)
{
	unsigned long long	result;
	size_t				i;
	size_t				neg;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
				neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		if (check_out_of_range(result, error, neg))
			break;
		i++;
	}
	return ((result * neg) % 256);
}

int	is_digit(char *arg)
{
	int	tmp;

	tmp = 0;
	if  (arg[tmp] == '-' ||	arg[tmp] == '+')
		tmp++;
	while (arg[tmp])
	{
		if ((arg[tmp] < 48 || arg[tmp] > 57))
			return (0);
		tmp++;
	}
	return (1);
}

void	ft_exit(t_tree *tree, t_shell *bash)
{	
	int	exit_code;
	int error;
	int	tmp;

	error = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!tree->lst_cmd->cmd[1])
		exit_code = 0;
	if (tree->lst_cmd->cmd[1])
	{
		tmp = 0;
		while (tree->lst_cmd->cmd[1][tmp] == ' ')
			tmp++;
		if (!is_digit(tree->lst_cmd->cmd[1] + tmp))
		{
			exit_code = 2;
			error = 1;
			printf("bash: exit: %s: numeric argument required\n", tree->lst_cmd->cmd[1]);
		}
		else
		{
			exit_code = ft_atoi_long(tree->lst_cmd->cmd[1], &error);
			if (error)
			{
				exit_code = 2;
				printf("bash: exit: %s: numeric argument required\n", tree->lst_cmd->cmd[1]);
			}
		}
		if (tree->lst_cmd->cmd[1] && tree->lst_cmd->cmd[2] && !error)
		{
			exit_code = 1;
			ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		}
	}
	free_shell(bash);
	exit(exit_code);
}
