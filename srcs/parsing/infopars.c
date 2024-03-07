/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infopars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:28 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 11:46:56 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_infopars	*diff_strshell(char *str, int i, int spe)
{
	int			x;
	t_infopars	*case;

	lib_memset(case, 0, sizeof(case));
	case->str = malloc((i + 1 * sizeof(char)));
	if (!case->str)
		return (NULL);
	x = -1;
	case->spe = spe;
	while (++x < i)
		case->str[x] = str[x];
	case->str[x] = '\0';
	case->next = NULL;
	return (case);
}

void	add_strshell(t_infopars *all, t_infopars *part)
{
	t_infopars	*curr_all;

	curr_all = all;
	if (all == NULL)
	{
		all = part;
		return ;
	}
	while (curr_all->next)
		curr_all = curr_all->next;
	curr_all->next = part;
}

void	free_strshell(t_infopars *all)
{
	t_infopars *curr_all;

	curr_all = all->next;
	while (curr_all)
	{
		free(all->str);
		free(all);
		all = curr_all;
		curr_all = curr_all->next;
	}
}
