/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infopars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:28 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 15:13:41 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

t_infopars	*diff_strshell(char *str, int i, int spe)
{
	int			x;
	t_infopars	*case_info;

	case_info = NULL;
	lib_memset(case_info, 0, sizeof(case_info));
	case_info->str = malloc((i + 1 * sizeof(char)));
	if (!case_info->str)
		return (NULL);
	x = -1;
	case_info->spe = spe;
	while (++x < i)
		case_info->str[x] = str[x];
	case_info->str[x] = '\0';
	case_info->next = NULL;
	return (case_info);
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

// void	build_lststr(char **str)
// {
// 	int	i;
	
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str_cmp())
// 	}
// }
