/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:01:47 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 13:50:45 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	free_and_process(t_lstcmd *lstprocess)
{
	t_lstcmd	*curr_and;

	curr_and = lstprocess;
	while (curr_and)
	{
		lstprocess = curr_and;
		free_def_process(lstprocess);
		if (lstprocess->or_next)
			free_or_process(lstprocess);
		curr_and = curr_and->and_next;
	}
}

void	free_or_process(t_lstcmd *lstprocess)
{
	t_lstcmd	*curr_or;

	curr_or = lstprocess->or_next;
	while (curr_or)
	{
		lstprocess = curr_or;
		free_def_process(lstprocess);
		if (lstprocess->and_next)
			free_and_process(lstprocess);
		curr_or = curr_or->or_next;
	}
}

void	free_def_process(t_lstcmd *lstcmd)
{
	t_lstcmd	*allcmd;

	allcmd = lstcmd;
	while (allcmd)
	{
		lstcmd = allcmd;
		free_split(lstcmd->cmd);
		free_split(lstcmd->t_path);
		if (allcmd->and_next)
			free_and_process(allcmd);
		if (allcmd->or_next)
			free_or_process(allcmd);
		allcmd = allcmd->def_next;
	}
}
