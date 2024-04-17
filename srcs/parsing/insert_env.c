/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:27:47 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 09:39:31 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static bool	join_tmp(t_data *x);
t_infopars	*lst_shellstr_env(char **str);

bool	replace_lstchar_env(t_infopars *lst_char, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 2)
		{
			if (!expander(curr, bash))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

bool	expander(t_infopars *curr, t_shell *bash)
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
		curr = true_expand(curr, tmp, bash);
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
	int		i;

	i = 0;
	lib_memset(&x, 0, sizeof(x));
	x.new_str = NULL;
	while (str[i])
	{
		if (str[i] != '$')
		{
			x.tmp = strup_to(str + i, skip_not_env(str + i));
			if (!x.tmp)
				return (NULL);
			i += skip_not_env(str + i);
		}
		else if (str[i++] == '$')
		{
			take_value(str + i, bash, &x);
			i += name_env(str + i);
		}
		if (!join_tmp(&x))
			return (NULL);
	}
	return (free(str), x.new_str);
}

static bool	join_tmp(t_data *x)
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

char	*env_value(char *str, t_envlist *lst_envs, int i, t_shell *bash)
{
	t_envlist	*curr;

	curr = lst_envs;
	if (str_len(str) == 0 || (str[0] != '?' && !is_char(str[0]) && \
	!is_num(str[0])))
		return (lib_strup("$"));
	else if (str[0] == '?')
		return (ft_itoa(bash->last_exit_status));
	while (curr)
	{
		if (str_ncmp(str, curr->key, i) && str_len(curr->key) == i)
			return (lib_strup(curr->value));
		curr = curr->next;
	}
	return (lib_strup(""));
}
