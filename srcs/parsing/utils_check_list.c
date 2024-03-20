/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:30:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 16:55:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	in_process(char c, t_token *token)
{
	if ((c == '|' || c == '&' || c == ';') && !token->in_process && \
	!token->in_doquote && !token->in_sgquote)
		token->in_process = true;
	else if (c != '|' && c != '&' && c != ';' && c != 32 && c != '\n' && \
	token->in_process && c != ')')
		token->in_process = false;
}

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

void	in_parsing(char c, t_token *token)
{
	if (c == '(' && !token->in_doquote && !token->in_sgquote)
		token->in_par++;
	else if (c == ')' && token->in_par && !token->in_sgquote && \
!token->in_doquote)
		token->in_par--;
	else if (c == ')' && !token->in_par && !token->in_sgquote && \
!token->in_doquote)
		token->error = true;
}
