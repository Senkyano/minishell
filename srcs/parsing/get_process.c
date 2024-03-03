/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/03 19:29:13 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	get_all_process(char *process, t_shell *bash)
{
	int	i;

	i = -1;
	bash->space = lib_split(process, " ");
	if (!bash->space)
		gestion_exit("Malloc fail\n", bash);
	while (bash->space[++i])
	{
	// analyse du space.
	// Dans le get process on auras d'abord le get_all_cmd.
		// Je vais devoir faire un split entre pipe
	}
}
