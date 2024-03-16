/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:44:08 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/16 19:08:30 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	process_befo(t_infopars *pre, t_token *token);
static void	check_bef_par(char *str, t_token *token);

bool	check_process(t_infopars *pars)
{
	t_infopars	*curr;
	t_token		token;

	curr = pars;
	lib_memset(&token, 0, sizeof(token));
	while (curr)
	{
		if (curr->str[0] == '(' && curr->prec)
			process_befo(curr->prec, &token);
		check_bef_par(curr->str, &token);
		curr = curr->next;
	}
	if (token.error)
	{
		printf_error(RED"-- Unexpected token --\n"RST);
		return (false);
	}
	return (true);
}

static void	check_bef_par(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		in_doquote(str[i], token);
		in_sgquote(str[i], token);
		if (str[i + 1] == '(' && str[i] != '|' && str[i] != '&' && \
		!token->in_doquote && !token->in_sgquote)
			token->error = true;
		i++;
	}
}

static void	process_befo(t_infopars *pre, t_token *token)
{
	int	i;

	i = str_len(pre->str);
	i--;
	if (pre->str[i] != '|' && pre->str[i] != '&' && !token->in_doquote && \
	!token->in_sgquote)
		token->error = true;
}
