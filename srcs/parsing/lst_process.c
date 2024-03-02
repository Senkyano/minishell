/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:37:44 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/02 22:26:00 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_body	*bloc_process(t_lstcmd *lstcmd, int prio)
{
	t_body	*process;

	lib_memset(process, 0, sizeof(process));
	process->prio = prio;
	process->allcmd = lstcmd;
	process->next = NULL;
	return (process);
}

void	add_proccess(t_shell *bash, t_body *process)
{
	t_body	*curr_process;

	curr_process = bash->process;
	if (!bash->process)
	{
		bash->process = process;
		return ;
	}
	while (curr_process->next != NULL)
		curr_process = curr_process->next;
	curr_process->next = process;
}
