/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:22:16 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/21 15:38:18 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infopars	*last_infile(t_infopars *lst_char)
{
	t_infopars	*curr;
	t_infopars	*last;

	curr = lst_char;
	last = NULL;
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
	return (last);
}

void	last_outfile(t_infopars *lst_char, t_lstcmd *curr_cmd) // ajoute la redirection ambigious
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 4)
		{
			if (curr->str[0] == '>')
			{
				if (curr_cmd->out_file > 0)
					close(curr_cmd->out_file);
				if (str_len(curr->str) == 1)
					curr_cmd->out_file = open(curr->next->str, O_CREAT | \
				O_WRONLY | O_TRUNC, 0644);
				else if (str_len(curr->str) == 2)
					curr_cmd->out_file = open(curr->next->str, O_CREAT | \
				O_WRONLY | O_APPEND, 0644);
			}
		}
		if (curr->spe == 5 || curr->spe == 1 || curr->spe == 0)
			return ;
		curr = curr->next;
	}
}
