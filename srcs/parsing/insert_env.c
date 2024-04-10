/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:27:47 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/10 15:33:03 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static char	*env_value(char *str, t_envlist *lst_envs, int i);
static void	join_tmp(t_data *x);

bool	replace_lstchar_env(t_infopars *lst_char, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{
		if (curr->spe == 2)
		{
			curr->str = insert_env(curr->str, bash);
			if (!curr->str)
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}

char	*insert_env(char *str, t_shell *bash)
{
	t_data	x;
	int		i;

	i = 0;
	lib_memset(&x, 0, sizeof(x));
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
			x.new_str = opti_join(x.new_str, env_value(str + i, bash->lst_envs, \
			name_env(str + i)));
			if (!x.new_str)
				return (NULL);
			i += name_env(str + i);
		}
		join_tmp(&x);
	}
	return (free(str), x.new_str);
}

static void	join_tmp(t_data *x)
{
	if (!x->new_str && x->tmp)
	{
		x->new_str = lib_strup(x->tmp);
		free(x->tmp);
		x->tmp = NULL;
		if (!x->new_str)
			return ;
	}
	else if (x->new_str && x->tmp)
	{
		x->new_str = opti_join(x->new_str, x->tmp);
		free(x->tmp);
		x->tmp = NULL;
		if (!x->new_str)
			return ;
	}
}

static char	*env_value(char *str, t_envlist *lst_envs, int i)
{
	t_envlist	*curr;

	curr = lst_envs;
	while (curr)
	{
		if (str_ncmp(str, curr->key, i) && str_len(curr->key) == i)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
