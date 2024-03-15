/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:30:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/15 19:23:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

bool	valid_str(char *str)
{
	t_token	token;
	int		i;

	i = -1;
	if (!str || str == 0)
		return (false);
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_sgquote(str[i], &token);
		in_doquote(str[i], &token);
		in_parsing(str[i], &token);
		in_process(str[i], &token);
	}
	if (!token.in_par && !token.in_doquote && !token.in_sgquote && \
	!token.error && !token.in_process)
		return (true);
	return (false);
}

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
