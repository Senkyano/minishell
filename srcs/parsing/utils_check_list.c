/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:30:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/21 18:42:30 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	in_sgquote(char c, t_token *token)
{
	if (c == 39 && !token->in_doquote && !token->in_sgquote)
		token->in_sgquote = true;
	else if (c == 39 && !token->in_doquote && token->in_sgquote)
		token->in_sgquote = false;
}

void	in_doquote(char c, t_token *token)
{
	if (c == '"' && !token->in_doquote && !token->in_sgquote)
		token->in_doquote = true;
	else if (c == '"' && token->in_doquote && !token->in_sgquote)
		token->in_doquote = false;
}

bool	in_feature(t_infopars *curr, t_shell *bash)
{
	if (curr->str[0] == ';' || curr->str[0] == '\\')
	{
		bash->exit_status = 2;
		printf_error(RED" -- Feature not include '%s' --\n", curr->str);
		return (false);
	}
	return (true);
}
