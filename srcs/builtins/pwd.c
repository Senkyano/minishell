/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:17:18 by yrio              #+#    #+#             */
/*   Updated: 2024/04/11 11:20:16 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args_split)
{
	char	*dir_path;

	if (args_split[1] && args_split[1][0] && args_split[1][0] == '-')
	{
		printf("bash: pwd: -%c: invalid option\n", args_split[1][1]);
		return (2);
	}
	dir_path = NULL;
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("getcwd"), 1);
	ft_putstr_fd(dir_path, 1);
	printf("\n");
	free(dir_path);
	return (0);
}
