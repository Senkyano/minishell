/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 13:50:53 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	free_shell(t_shell *bash)
{
	if (bash->path)
		free_split(bash->path);
	if (bash->str_split)
		free_split(bash->str_split);
	if (bash->lstcmd)
		free_and_process(bash->lstcmd);
	if (bash->lst_char)
		free_strshell(bash->lst_char);
	// if (bash->env)
	// 	free_env(bash->env);
}
