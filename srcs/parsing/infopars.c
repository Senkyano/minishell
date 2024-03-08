/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infopars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:28 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/08 17:13:38 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_infopars	*diff_strshell(char *str, int spe)
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
	case_info->next = NULL;
	return (case_info);
}

void	add_strshell(t_infopars **all, t_infopars *part)
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
	}
}

void	free_strshell(t_infopars **all)
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
