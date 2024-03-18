/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:19:06 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/18 17:11:42 by rihoy            ###   ########.fr       */
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
			new_data.new_lst = cut_strshell(curr->str); // prototype
			add_btw_strshell(curr->prec, new_data.new_lst, curr->next, &curr);
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

	nbr_cmd = 1;
	i = -1;
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (!token.in_doquote && !token.in_sgquote && (str[i] == '|' || \
		str[i] == '&'))
			nbr_cmd++;
	}
	if (nbr_cmd == 1)
		return (false);
	return (true);
}

int	next_process(char *str)
{
	t_token	token;
	int		i;

	i = -1;
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (!token.in_doquote && !token.in_sgquote && \
		(str[i] == '|' || str[i] == '&'))
			return (i);
	}
	return (i);
}

t_infopars	*cut_strshell(char *str)
{
	t_data		tmp;

	lib_memset(&tmp, 0, sizeof(tmp));
	while (str[tmp.i])
	{
		// creation de la nouvelle liste
	}
	return (new_lst);
}//faire une nouvelle liste grace au char.
