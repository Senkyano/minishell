/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:47:11 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/18 22:54:28 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	malloc_proc(t_data *tmp, char *str)
{
	if (str[tmp.i] == '&')
	{
		tmp.tmp_box = diff_strshell("&&", 5);
		if (!tmp.tmp_box)
		{
			if (tmp.new_lst)
				free_strshell(tmp.new_lst);
			return (false);
		}
	}
}
