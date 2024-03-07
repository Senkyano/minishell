/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:30:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 21:34:22 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

bool	valid_str(char *str)
{
	t_token	token;
	int		i;

	i = -1;
	lib_memset(&token, 0, sizeof(token));
	while (str[++i])
	{
		in_sgquote(str[i], &token);
		in_doquote(str[i], &token);
		in_parsing(str[i], &token);
	}
	if (last_cmp(str, "&&\n") || last_cmp(str, "||\n") || last_cmp(str, "|\n"))
		token.error = true;
	if (!token.in_par && !token.in_doquote && !token.in_sgquote && !token.error)
		return (true);
	return (false);
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