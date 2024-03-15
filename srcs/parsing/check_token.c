/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:42:19 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/15 14:41:35 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	insepct_token(char *str, t_token *token);

bool	valid_token(char *str)
{
	t_token	token;
	int		i;

	i = skip_space(str);
	lib_memset(&token, 0, sizeof(token));
	if (str[i] == '|' || str[i] == '&')
	{
		printf_error(CY"Minishell >: "RED"-- Unexpected token --\n"RST);
		return (false);
	}
	while (str[i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		in_parsing(str[i], &token);
		in_process(str[i], &token);
		i += insepct_token(&str[i], &token);
		i++;
	}
	if (!token.error)
		return (true);
	printf_error(CY"Minishell >: "RED"-- Unexpected token --\n"RST);
	return (false);
}

int	insepct_token(char *str, t_token *token)
{
	int	i;

	i = skip_space(str + 1);
	if (!token->in_doquote && !token->in_sgquote && str[0] == '|' && \
	str[i + 1] == '|' && i > 1)
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && str[0] == '(' && \
	(str[i + 1] == '|' || str[i + 1] == '&'))
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && (str[0] == '|' || \
	str[0] == '&') && str[i + 1] == ')')
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && str[0] == '&' && \
	str[1] == '&')
		return (1);
	else if (!token->in_doquote && !token->in_sgquote && str[0] == '&' && \
	str[1] != '&')
		token->error = true;
	return (i);
}
