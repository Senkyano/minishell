/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:22:16 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/11 13:40:24 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



bool	exist_outfile(t_infopars *lst_char)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 3 && curr->prec->str[0] == '>')
			return (true);
		else if (curr->spe == 0 || curr->spe == 1 || curr->spe == 5)
			return (false);
		curr = curr->next;
	}
	return (false);
}

bool	exist_infile(t_infopars *lst_char)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 3 && curr->prec->str[0] == '<')
			return (true);
		else if (curr->spe == 0 || curr->spe == 1 || curr->spe == 5)
			return (false);
		curr = curr->next;
	}
	return (false);
}

t_infopars	*last_infile(t_infopars *lst_char)
{
	t_infopars	*curr;
	t_infopars	*last;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 4)
		{
			if (curr->str[0] == '<' && str_len(curr->str) == 1)
				last = curr->next;
		}
		if (curr->spe == 5 || curr->spe == 1 || curr->spe == 0)
			return (last);
		curr = curr->next;
	}
	return (NULL);
}

t_infopars	*last_outfile(t_infopars *lst_char)
{
	t_infopars	*curr;
	t_infopars	*last;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 4)
		{
			if (curr->str[0] == '>')
				last = curr->next;
		}
		if (curr->spe == 5)
			return (last);
		curr = curr->next;
	}
	return (NULL);
}
