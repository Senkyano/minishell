/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:28 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/16 14:22:45 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_infopars	*diff_boxshell(char *str, int spe)
{
	int			x;
	t_infopars	*case_info;

	case_info = malloc(sizeof(t_infopars));
	if (!case_info)
		return (NULL);
	case_info->str = malloc(((str_len(str) + 1) * sizeof(char)));
	if (!case_info->str)
		return (free(case_info), NULL);
	x = -1;
	case_info->spe = spe;
	while (str[++x])
		case_info->str[x] = str[x];
	case_info->str[x] = '\0';
	case_info->spe = spe;
	case_info->next = NULL;
	case_info->prec = NULL;
	return (case_info);
}

void	add_btw_boxshell(t_infopars *pre, t_infopars *new_lst, \
t_infopars *next, t_infopars **old)
{
	t_infopars	*curr;

	if (pre)
	{
		pre->next = new_lst;
		new_lst->prec = pre;
	}
	curr = new_lst;
	while (curr->next)
		curr = curr->next;
	if (next)
	{
		curr->next = next;
		next->prec = curr;
	}
	(*old)->next = NULL;
	(*old)->prec = NULL;
	free_blockstrshell((*old));
	(*old) = curr;
}

void	add_boxshell(t_infopars **all, t_infopars *part)
{
	t_infopars	*curr_all;

	if ((*all) == NULL)
		(*all) = part;
	else
	{
		curr_all = (*all);
		while (curr_all->next != NULL)
			curr_all = curr_all->next;
		curr_all->next = part;
		part->prec = curr_all;
	}
}

void	free_boxshell(t_infopars **all)
{
	t_infopars	*curr_all;

	curr_all = *all;
	while ((*all))
	{
		curr_all = (*all);
		(*all) = (*all)->next;
		free(curr_all->str);
		free(curr_all);
	}
}

void	print_boxshell(t_infopars *lst)
{
	t_infopars	*curr;

	curr = lst;
	while (curr)
	{
		printf_error("%s ", curr->str);
		curr = curr->next;
	}
}
