/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthese2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:07:48 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/12 18:22:30 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	good_af_pars2(t_infopars *next, t_infopars *curr, t_shell *bash)
{
	if (next)
	{
		if (curr->str[0] == ')' && next->str[0] != ')' && \
		!is_operator(next->str[0]))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", next->str);
			bash->exit_status = 2;
			return (false);
		}
	}
	return (true);
}
