/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:25:27 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/27 21:33:21 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmd(t_infopars *lst)
{
	t_infopars	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr)
	{
		if (curr->spe == 2)
			i++;
		else if (curr->spe == 5 || curr->spe == 1 || curr->spe == 0)
			return (i);
		curr = curr->next;
	}
	return (i);
}
