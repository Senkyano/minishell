/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:49:30 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 16:55:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	get_true_path(t_shell *bash, char const **env)
{
	int	i;

	i = 0;
	while (env[i] && !str_ncmp((char *)env[i], "PATH=", 5))
		i++;
	if (str_ncmp((char *)env[i], "PATH=", 5))
	{
		bash->path = lib_split((char *)env[i] + 5, ":");
		if (!bash->path)
			gestion_exit("Malloc fail", bash);
	}
	else
		gestion_exit("PATH= not found", bash);
	i = -1;
	while (bash->path[++i])
	{
		bash->path[i] = str1_join(bash->path[i], "/");
		if (!bash->path[i])
			gestion_exit("Malloc fail", bash);
	}
}
