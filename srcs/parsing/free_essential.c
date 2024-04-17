/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_essential.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:54:23 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 12:10:18 by rihoy            ###   ########.fr       */
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

void	eradication(t_shell *bash)
{
	if (bash->lst_char)
		free_boxshell(&bash->lst_char);
	if (bash->tree)
		free_tree(bash->tree);
	if (bash->path)
		lib_free_split(bash->path);
	if (bash->str_split)
		lib_free_split(bash->str_split);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
	close(bash->std_in);
	close(bash->std_out);
	exit(bash->exit_status);
}
