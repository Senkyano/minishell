/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lst_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:52:58 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/22 15:07:41 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	calcul_pars(t_token *token, t_shell *bash);

bool	check_lst_split(t_shell *bash)
{
	t_infopars	*curr;
	t_token		token;

	curr = bash->lst_char;
	lib_memset(&token, 0, sizeof(token));
	while (curr)
	{
		if (!finish_quote(curr->str, &token, bash) || \
		!good_operator(curr->str, bash) || !in_feature(curr, bash) || \
		!before_operator(curr, curr->prec, bash) || \
		!after_operator(curr->prec, curr, curr->next, bash) || \
		!check_pars(curr, &token, bash))
			return (false);
		curr = curr->next;
	}
	if (!calcul_pars(&token, bash))
		return (false);
	return (true);
}

bool	calcul_pars(t_token *token, t_shell *bash)
{
	token->tot_pars = token->in_pars - token->out_pars;
	if (token->tot_pars > 0)
	{
		printf_error(RED" -- Feature not Include --\n"RST);
		bash->exit_status = 2;
		return (false);
	}
	else if (token->tot_pars < 0)
	{
		printf_error(RED" -- Unexpected token ')' --\n"RST);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}
