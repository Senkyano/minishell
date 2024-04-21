/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/21 15:03:19 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static bool	start_process(char *str, t_shell *bash);
void		free_lstchar(t_infopars *lst_char);
t_infopars	*noeud_first(t_infopars *lst_char);

bool	build_process(char *str, t_shell *bash)
{
	t_infopars	*curr;

	if (!str_len(str) || only_space(str))
		return (free(str), false);
	if (!start_process(str, bash))
	{
		free(bash->str_split);
		free_essential(bash);
		return (false);
	}
	curr = last_boxshell(bash->lst_char);
	curr = noeud_first(curr);
	if (!building_tree(&bash->tree, curr, bash))
	{
		if (bash->tree)
		{
			close_tree(bash->tree);
			free_essential(bash);
			bash->tree = NULL;
		}
		return (false);
	}
	free_lstchar(bash->lst_char);
	bash->lst_char = NULL;
	return (true);
}

static bool	lst_shellstr(t_shell *bash)
{
	int			i;
	t_infopars	*tmp;

	i = -1;
	while (bash->str_split[++i])
	{
		tmp = diff_boxshell(bash->str_split[i], 1);
		if (!tmp)
		{
			printf_error(RED"Malloc fail\n"RST);
			free_split(bash->str_split);
			return (false);
		}
		add_boxshell(&bash->lst_char, tmp);
	}
	lib_free_split(bash->str_split);
	bash->str_split = NULL;
	return (true);
}

static bool	start_process(char *str, t_shell *bash)
{
	add_history(str);
	bash->str_split = split_minishell(str);
	if (!bash->str_split)
	{
		free(str);
		printf_error(RED"Malloc fail\n"RST);
		return (false);
	}
	if (bash->str_split[0][0] == 0 || !lst_shellstr(bash))
		return (false);
	listing_split(bash);
	if (!check_lst_split(bash))
		return (false);
	id_shellst(bash);
	if (sub_shell(bash->lst_char, bash))
		return (false);
	if (!replace_lstchar_env(bash->lst_char, bash))
		return (false);
	if (!suppress_quote(bash->lst_char))
		return (false);
	return (true);
}

t_infopars	*noeud_first(t_infopars *lst_char)
{
	t_infopars	*curr;
	t_infopars	*last;
	int			par;

	par = 0;
	curr = lst_char;
	last = curr;
	while (curr)
	{
		if (curr->spe == 0)
		{
			if (curr->str[0] == '(')
				par--;
			else if (curr->str[0] == ')')
				par++;
		}
		if (curr->spe == 1 && par == 0)
			return (curr);
		else if (par < 0)
			return (last);
		last = curr;
		curr = curr->prec;
	}
	return (last);
}

void	free_lstchar(t_infopars *lst_char)
{
	t_infopars	*curr;

	while (lst_char)
	{
		curr = lst_char;
		lst_char = lst_char->next;
		if (curr->spe != 2)
			free_blockstrshell(curr);
		else if (curr->spe == 2)
			free(curr);
	}
}
