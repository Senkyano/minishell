/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_insert_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:45:18 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 19:00:50 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_box(t_infopars *curr);

bool	space_in_expand(char *str)
{
	t_token	token;
	int		i;

	i = -1;
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (!token.in_doquote && !token.in_sgquote && str[i] == ' ')
			return (true);
	}
	return (false);
}

t_infopars	*true_expand(t_infopars *curr, char **str, t_shell *bash)
{
	t_infopars	*new_lst;
	t_infopars	*next;
	t_infopars	*last_new;
	t_infopars	*prec;

	prec = curr->prec;
	next = curr->next;
	new_lst = lst_shellstr_env(str);
	if (!new_lst)
	{
		printf_error(RED"Malloc fail\n"RST);
		lib_free_split(str);
		return (NULL);
	}
	if (prec)
		prec->next = new_lst;
	else if (!prec)
		bash->lst_char = new_lst;
	last_new = last_boxshell(new_lst);
	last_new->next = next;
	if (curr)
		free_box(curr);
	return (last_new);
}

void	free_box(t_infopars *curr)
{
	if (curr->str)
		lib_free_split(&curr->str);
	free(curr);
}

bool	take_value(char *str, t_shell *bash, t_data *x)
{
	char	*tmp;

	tmp = env_value(str, bash->lst_envs, name_env(str), bash);
	if (!tmp)
		return (false);
	x->new_str = opti_join(x->new_str, tmp);
	free(tmp);
	if (!x->new_str)
		return (false);
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
