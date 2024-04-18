/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:27:47 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/18 14:00:57 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_infopars	*lst_shellstr_env(char **str);

bool	replace_lstchar_env(t_infopars *lst_char, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 2)
		{
			if (!expander(curr, bash, &curr))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	expander(t_infopars *curr, t_shell *bash, t_infopars **new_curr)
{
	char	**tmp;

	tmp = NULL;
	curr->str = insert_env(curr->str, bash);
	if (!curr->str)
	{
		printf_error(RED"Malloc fail\n"RST);
		return (false);
	}
	if (space_in_expand(curr->str))
	{
		tmp = split_minishell(curr->str);
		if (!tmp)
			return (false);
		curr->str = NULL;
		*new_curr = true_expand(curr, tmp, bash);
		if (!curr)
			return (false);
	}
	return (true);
}

t_infopars	*lst_shellstr_env(char **str)
{
	t_infopars	*new_lst;
	t_infopars	*tmp;
	int			i;

	i = -1;
	new_lst = NULL;
	while (str[++i])
	{
		tmp = diff_boxshell(str[i], 2);
		if (!tmp)
		{
			printf_error(RED"Malloc fail\n"RST);
			free_split(str);
			return (NULL);
		}
		add_boxshell(&new_lst, tmp);
	}
	lib_free_split(str);
	return (new_lst);
}

char	*insert_env(char *str, t_shell *bash)
{
	t_data	x;
	t_token	token;
	int		i;

	i = 0;
	lib_memset(&token, 0, sizeof(token));
	lib_memset(&x, 0, sizeof(x));
	x.new_str = NULL;
	while (str[i])
	{
		i += change_(str + i, bash, &x, &token);
		if (i == -1)
		{
			if (x.new_str)
				free(x.new_str);
			if (x.tmp)
				free(x.tmp);
			return (free(str), NULL);
		}
		if (!join_tmp(&x))
			return (NULL);
	}
	return (free(str), x.new_str);
}

bool	join_tmp(t_data *x)
{
	if (!x->new_str && x->tmp)
	{
		x->new_str = lib_strup(x->tmp);
		free(x->tmp);
		x->tmp = NULL;
		if (!x->new_str)
			return (false);
	}
	else if (x->new_str && x->tmp)
	{
		x->new_str = opti_join(x->new_str, x->tmp);
		free(x->tmp);
		x->tmp = NULL;
		if (!x->new_str)
			return (false);
	}
	return (true);
}
