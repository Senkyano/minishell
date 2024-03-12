/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:44:33 by yrio              #+#    #+#             */
/*   Updated: 2024/03/12 09:42:29 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_shell(t_shell *minishell, char **argv, char **env)
{
	int		tmp;

	minishell->exit_status = 0;
	minishell->path = get_paths(env);
	tmp = 0;
	while (minishell->path[tmp++])
		minishell->path[tmp] = ft_strjoin_gnl(minishell->path[tmp], "/", 1);
	minishell->nbr_path = tmp;
	
	free_split(minishell->path);
}
