/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:19:06 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/19 17:07:15 by rihoy            ###   ########.fr       */
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
			new_data.new_lst = cut_boxshell(curr->str);
			if (!new_data.new_lst)
				return ;
			add_btw_boxshell(curr->prec, new_data.new_lst, curr->next, &curr);
			bash->lst_char = first_boxshell(curr);
		}
		else if (!curr->str || curr->str[0] == 0)
			curr = supp_blockshell(curr->prec, curr->next, curr);
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

t_infopars	*cut_boxshell(char *str)
{
	t_data		tmp;
	t_token		token;

	lib_memset(&token, 0, sizeof(token));
	lib_memset(&tmp, 0, sizeof(tmp));
	while (str[tmp.i])
	{
		if (str[tmp.i] != '|' && str[tmp.i] != '&')
		{
			tmp.new_str = strup_to(str + tmp.i, next_process(str + tmp.i));
			if (!tmp.new_str)
			{
				if (tmp.new_lst)
					free_boxshell(&tmp.new_lst);
				return (NULL);
			}
			tmp.tmp_box = diff_boxshell(tmp.new_str, 1);
			free(tmp.new_str);
			tmp.new_str = NULL;
			if (!tmp.tmp_box)
			{
				free(tmp.new_str);
				if (tmp.new_lst)
					free_boxshell(&tmp.new_lst);
				return (NULL);
			}
			add_boxshell(&tmp.new_lst, tmp.tmp_box);
			tmp.i += next_process(str + tmp.i);
		}
		else if (str[tmp.i] == '|' || str[tmp.i] == '&')
			tmp.i++; // add les pipes et && puis les redirections
	}
	return (tmp.new_lst);
}//faire une nouvelle liste grace au char.
