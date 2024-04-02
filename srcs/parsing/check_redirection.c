/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:28:21 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 12:17:25 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redirection(t_infopars *curr, t_shell *bash)
{
	if (curr)
	{
		if ((curr->str[0] == '>' || curr->str[0] == '<') && !curr->next)
		{
			printf_error(RED" -- Unexpected token 'newline' --\n"RST);
			bash->exit_status = 2;
			return (false);
		}
		if (curr->prec)
		{
			if ((curr->str[0] == '>' || curr->str[0] == '<') && \
			(curr->prec->str[0] == '>' || curr->prec->str[0] == '<'))
			{
				printf_error(RED" -- Unexpected token '%s' --\n"\
				RST, curr->prec->str);
				bash->exit_status = 2;
				return (false);
			}
		}
	}
	return (true);
}
