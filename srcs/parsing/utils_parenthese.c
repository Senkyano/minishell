/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthese.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:40:00 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/22 23:02:51 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	good_bef_pars(t_infopars *pre, t_infopars *curr, t_shell *bash);
bool	good_af_pars(t_infopars *next, t_infopars *curr, t_shell *bash);

bool	check_pars(t_infopars *curr, t_token *token, t_shell *bash)
{
	if (!good_bef_pars(curr->prec, curr, bash) || \
	!good_af_pars(curr->next, curr, bash))
		return (false);
	if (curr->str[0] == '(')
	{
		token->in_pars += str_len(curr->str);
		if ((str_len(curr->str) > 1 || (curr->prec && curr->prec->str[0] == '(')))
			token->d_in_pars = true;
	}
	else if (curr->str[0] == ')')
	{
		token->out_pars += str_len(curr->str);
		if (str_len(curr->str) > 1 || (curr->prec && curr->prec->str[0] == ')'))
			token->d_out_pars = true;
	}
	if ((token->in_pars == token->out_pars - 1) || (token->in_pars - 1 == token->out_pars))
	{
		token->d_in_pars = false;
		token->d_out_pars = false;
	}
	if (token->d_out_pars && token->d_in_pars)
	{
		printf_error(RED" -- Unexpected token '%s' --\n", curr->prec->str);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}

bool	good_bef_pars(t_infopars *pre, t_infopars *curr, t_shell *bash)
{
	if (pre && curr->str[0] == '(')
	{
		if (pre->str[0] != '(' && !is_operator(pre->str[0]))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", curr->str);
			bash->exit_status = 2;
			return (false);
		}
	}
	if (!pre && curr->str[0] == ')')
	{
		printf_error(RED" -- Unexpected token '%s' --\n", curr->str);
		bash->exit_status = 2;
		return (false);
	}
	else if (pre && curr->str[0] == ')')
	{
		if (is_operator(pre->str[0]))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", curr->str);
			bash->exit_status = 2;
			return (false);
		}
	}
	return (true);
}

bool	good_af_pars(t_infopars *next, t_infopars *curr, t_shell *bash)
{
	if (next && curr->str[0] == '(')
	{
		if (curr->str[0] == '(' && (is_operator(next->str[0]) || \
		next->str[0] == ')'))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", next->str);
			bash->exit_status = 2;
			return (false);
		}
		if (curr->str[0] == ')' && !is_operator(next->str[0]))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", next->str);
			bash->exit_status = 2;
			return (false);
		}
	}
	else if (!next && curr->str[0] == '(')
	{
		printf_error(RED" -- Unexpected token '%s' --\n", curr->str);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}
