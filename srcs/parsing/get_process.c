/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/03 13:42:17 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	get_all_process(char *process, t_shell *bash)
{
	bash->space = lib_split(process, " ");
	if (!bash->space)
		gestion_exit("Malloc fail\n", bash);
	// Premiere choses a faire c'est de faire un un split pour tout les espace.
	// Dans le get process on auras d'abord le get_all_cmd.
		// Je vais devoir faire un split entre pipe
}
