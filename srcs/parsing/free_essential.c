/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_essential.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:54:23 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/10 16:20:31 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_essential(t_shell *bash)
{
	if (bash->lst_char)
	{
		free_boxshell(&bash->lst_char);
		bash->lst_char = NULL;
	}
	if (bash->tree)
	{
		free_tree(bash->tree);
		bash->tree = NULL;
	}
}
