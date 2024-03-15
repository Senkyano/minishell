/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infopars2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:03:39 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/15 16:46:51 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

t_infopars	*supp_blockshell(t_infopars *pre, t_infopars *next, t_infopars *curr)
{
	if (next)
		pre->next = next;
	else
		pre->next = NULL;
	if (pre)
		next->prec = pre;
	else
		next->prec = NULL;
	curr->next = NULL;
	curr->prec = NULL;
	free_blockstrshell(curr);
	return (pre);
}

void	free_blockstrshell(t_infopars *selec)
{
	if (!selec->str || selec->str[0] == 0)
		free(selec->str);
	free(selec);
}
