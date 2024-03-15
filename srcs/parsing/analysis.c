/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:19:06 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/15 14:16:32 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

static bool	need_cut(char *str);

void	analysis_shell(t_shell *bash)
{
	t_data		new_data;
	t_infopars	*curr;

	curr = bash->lst_char;
	lib_memset(&new_data, 0, sizeof(new_data));
	while (curr)
	{
		if (curr->str && need_cut(curr->str))
		{
			new_data.new_lst =  NULL;// new liste;
		}
		else if (!curr->str || curr->str[0] == 0)
			curr = supp_blockshell(curr->prec, curr, curr->next);
		curr = curr->next;
	}
}

bool	need_cut(char *str)
{
	t_token	token;
	int		i;
	int		nbr_cmd;

	nbr_cmd = 0;
	i = -1;
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
	}
	return (true);
}

// t_infopars	*cut_strshell(char *str)
// {
	
// }//faire une nouvelle liste grace au char.
