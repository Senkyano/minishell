/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openning_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/11 19:18:24 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_heredoc(t_infopars	*lst_char, t_lstcmd *cmd, t_shell *bash)
{
	
}

bool	def_file(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = last_infile(lst_char);
	if (curr)
	{
		if (curr->prec->str[0] == '<' && str_len(curr->prec->str) == 1)
		{
			cmd->in_file_name = lib_strup(curr->str);
			if (!cmd->in_file_name)
				return (false);
		}
	}
	curr = last_outfile(lst_char);
	if (curr)
	{
		if (str_len(curr->prec->str) == 1)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (str_len(curr->prec->str) == 2)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_file < 0)
		{
			bash->exit_status = 127;
			return (false);
		}
	}
}

void	define_last_in(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr && curr->spe != 5 && curr->spe != 1 && curr->spe != 0)
	{
		if (curr->spe == 3 && curr->str[0] == '<')
		{
			if (str_len(curr->str) == 1)
				cmd->last_infile = NO_HERE_DOC;
			else if (str_len(curr->str) == 2)
				cmd->last_infile = HERE_DOC;
		}
		curr = curr->next;
	}
}
