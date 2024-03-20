/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 19:14:57 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static bool	start_process(char *str, t_shell *bash);

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
	free_split(bash->str_split);
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
	t_infopars	*curr;

	curr = bash->lst_char;
	while (curr)
	{
		// curr->str = insert_env(curr->str, bash);
		if (curr->str)
		{
			printf_error("%s\n", curr->str);
		}
		else if (!curr->str || curr->str[0] == 0)
			printf_error("! supp !");
		curr = curr->next;
	}
	return (true);
}
