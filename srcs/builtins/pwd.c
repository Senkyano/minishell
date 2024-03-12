/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:17:18 by yrio              #+#    #+#             */
/*   Updated: 2024/03/12 14:54:00 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	ft_pwd(void)
{
	char	*dir_path;

	dir_path = NULL;
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("getcwd"));
	ft_putstr_fd(dir_path, 1);
	printf("\n");
	free(dir_path);
}