/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:25:27 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/28 10:13:39 by rihoy            ###   ########.fr       */
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

t_infopars	*process_left(t_infopars *lst, int parenthese)
{
	t_infopars	*curr;
	t_token		token;

	curr = lst;
	lib_memset(&token, 0, sizeof(token));
	while (curr->prec)
	{
		// if (token->in_pars)
		if (curr->spe == 1)
			return (curr);
		curr = curr->prec;
	}
	return (curr);
}

t_infopars	*process_right(t_infopars *lst, int parenthese)
{
	t_infopars	*curr;
	t_token		token;

	curr = lst;
	lib_memset(&token, 0, sizeof(token));
	while (curr->next)
	{
		if (curr->spe == 1)
			return (curr);
		curr = curr->next;
	}
	return (curr);
}
