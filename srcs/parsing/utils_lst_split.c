/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:47:11 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/28 14:56:07 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_operateur(char *str);

bool	box_process(t_data *tmp, char *str)
{
	tmp->new_str = strup_to(str, skip_operateur(str));
	if (!tmp->new_str)
	{
		if (tmp->new_lst)
			free_boxshell(&tmp->new_lst);
		return (false);
	}
	tmp->tmp_box = diff_boxshell(tmp->new_str, 0);
	if (!tmp->tmp_box)
	{
		if (tmp->new_lst)
			free_boxshell(&tmp->new_lst);
		return (false);
	}
	free(tmp->new_str);
	tmp->new_str = NULL;
	tmp->i += skip_operateur(str);
	add_boxshell(&tmp->new_lst, tmp->tmp_box);
	return (true);
}

bool	box_str(t_data *tmp, char *str)
{
	tmp->new_str = strup_to(str, next_process(str));
	if (!tmp->new_str)
	{
		if (tmp->new_lst)
			free_boxshell(&tmp->new_lst);
		return (false);
	}
	tmp->tmp_box = diff_boxshell(tmp->new_str, 0);
	if (!tmp->tmp_box)
	{
		if (tmp->new_lst)
			free_boxshell(&tmp->new_lst);
		return (false);
	}
	free(tmp->new_str);
	tmp->new_str = NULL;
	tmp->i += next_process(str);
	add_boxshell(&tmp->new_lst, tmp->tmp_box);
	return (true);
}

static int	skip_operateur(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!is_operator(str[i]) && str[i] != '(' && str[i] != ')' && \
		!is_redirection(str[i])) || str[i] != str[0])
			return (i);
		if ((str[i] == '(' || str[i] == ')'))
			return (1);
		i++;
	}
	return (i);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (true);
	return (false);
}

bool	is_redirection(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}
