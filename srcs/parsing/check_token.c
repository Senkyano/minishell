/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:42:19 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/17 00:08:12 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

static int	insepct_token(char *str, t_token *token);
static bool	after_token_cmd(char *str);
static void	under_pars(char *str, t_token *token);

bool	valid_token(char *str)
{
	t_token	token;
	int		i;

	i = skip_space(str);
	lib_memset(&token, 0, sizeof(token));
	if (str[i] == '|' || str[i] == '&')
		token.error = true;
	while (str[i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		in_parsing(str[i], &token);
		in_process(str[i], &token);
		under_pars(str + i, &token);
		if (str[i] == ')' && after_token_cmd(&str[i] + 1))
			token.error = true;
		i += insepct_token(&str[i], &token);
		i++;
	}
	if (!token.error && !token.enter_par)
		return (true);
	printf_error(RED"-- Unexpected token --\n"RST);
	return (false);
}

static void	under_pars(char *str, t_token *token)
{
	int	i;

	i = 0;
	if (str[i] == '(')
	{
		i++;
		i += skip_space(str + i);
		if (str[i] != '(' && !(is_char(str[i]) || is_num(str[i])))
			token->error = true;
	}
}

int	insepct_token(char *str, t_token *token)
{
	int	i;

	i = skip_space(str + 1);
	if (!token->in_doquote && !token->in_sgquote && str[0] == '|' && str[1] == '|' 
	&& str[2] == '|')
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && str[0] == '|' && 
	(str[i + 1] == '|' || str[i + 1] == '&') && i > 0)
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && str[0] == '(' && 
	(str[i + 1] == '|' || str[i + 1] == '&'))
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && (str[0] == '|' || 
	str[0] == '&') && str[i + 1] == ')')
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && ((str[0] == '&' && 
	str[1] == '|') || (str[0] == '|' && str[1] == '&')))
		token->error = true;
	if (!token->in_doquote && !token->in_sgquote && str[0] == '&' && \
	str[1] == '&' && after_token_cmd(str + 2))
		return (1 + i);
	else if (!token->in_doquote && !token->in_sgquote && str[0] == '&' && \
	str[1] == '&' && str[2] == '&')
		token->error =true;
	return (i);
}

bool	after_token_cmd(char *str)
{
	int	i;

	i = skip_space(str);
	if (str[i] == '(')
	{
		i++;
		i += skip_space(str + i);
	}
	if (is_char(str[i]) || is_num(str[i]))
		return (true);
	return (false);
}
