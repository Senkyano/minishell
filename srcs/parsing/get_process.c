/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/08 22:00:00 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static bool	start_process(char *str, t_shell *bash);
void	free_lstchar(t_infopars *lst_char);

bool	build_process(char *str, t_shell *bash)
{
	if (!str_len(str))
		return (false);
	if (!start_process(str, bash))
		return (false);
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
	bash->str_split = split_minishell(str);
	if (!bash->str_split)
	{
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
	replace_lstchar_env(bash->lst_char, bash);
	t_infopars *curr;

	curr = last_boxshell(bash->lst_char);
	// build_tree(curr, &bash->tree);
	if (!building_tree(&bash->tree, curr))
		return (false);
	if (!bash->tree)
		return (false);
	free_lstchar(bash->lst_char);
	bash->lst_char = NULL;
	return (true);
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
