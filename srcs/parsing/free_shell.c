/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:27:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/13 11:45:29 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

void	free_shell(t_shell *bash)
{
	if (bash->path)
		lib_free_split(bash->path);
	if (bash->str_split)
		lib_free_split(bash->str_split);
	if (bash->lstcmd)
		free_and_process(bash->lstcmd);
	if (bash->lst_char)
		free_strshell(&bash->lst_char);
	if (bash->lst_envs)
		lstclear(bash->lst_envs);
}
