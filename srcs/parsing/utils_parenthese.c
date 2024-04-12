/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parenthese.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:40:00 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/12 18:23:41 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	good_bef_pars(t_infopars *pre, t_infopars *curr, t_shell *bash);
static bool	good_af_pars(t_infopars *next, t_infopars *curr, t_shell *bash);
bool		count_out_pars(t_infopars **curr, t_infopars *pre, t_token *token);
void		count_in_pars(t_infopars **curr, t_token *token);

bool	check_pars(t_infopars **curr, t_token *token, t_shell *bash)
{
	if (!good_bef_pars((*curr)->prec, (*curr), bash) || \
	!good_af_pars((*curr)->next, (*curr), bash) || \
	!good_af_pars2((*curr)->next, (*curr), bash))
		return (false);
	count_in_pars(curr, token);
	if (!count_out_pars(curr, (*curr)->prec, token))
		return (false);
	if (token->in_pars < token->out_pars)
	{
		printf_error(RED" -- Unexpected token ')' --\n"RST);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}

static bool	good_bef_pars(t_infopars *pre, t_infopars *curr, t_shell *bash)
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

static bool	good_af_pars(t_infopars *next, t_infopars *curr, t_shell *bash)
{
	if (curr->str[0] == '(' && next)
	{
		if (curr->str[0] == '(' && (is_operator(next->str[0]) || \
		next->str[0] == ')'))
		{
			printf_error(RED" -- Unexpected token '%s' --\n", next->str);
			bash->exit_status = 2;
			return (false);
		}
		else if (curr->str[0] == ')' && !is_operator(next->str[0]))
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

void	count_in_pars(t_infopars **curr, t_token *token)
{
	if ((*curr)->str[0] == '(')
	{
		while ((*curr) && (*curr)->str[0] == '(')
		{
			token->in_pars += str_len((*curr)->str);
			if (str_len((*curr)->str) > 1)
				token->in_pars_suite = true;
			else if ((*curr)->prec && (*curr)->prec->str[0] == '(' && \
			(*curr)->str[0] == '(')
				token->in_pars_suite = true;
			(*curr) = (*curr)->next;
		}
	}
}

bool	count_out_pars(t_infopars **curr, t_infopars *pre, t_token *token)
{
	if ((*curr)->str[0] == ')')
	{
		while ((*curr) && (*curr)->str[0] == ')')
		{
			token->out_pars += str_len((*curr)->str);
			if (str_len((*curr)->str) > 1)
				token->out_pars_suite = true;
			else if ((*curr)->prec && (*curr)->prec->str[0] == ')' \
			&& (*curr)->str[0] == ')')
				token->out_pars_suite = true;
			if (token->out_pars_suite && token->in_pars_suite)
			{
				printf_error(RED" -- Unexpected token '%s' --\n"RST, pre->str);
				return (false);
			}
			(*curr) = (*curr)->next;
		}
		if ((*curr) && (*curr)->prec->str[0] == ')' && \
		!is_operator((*curr)->str[0]) && token->in_pars_suite)
		{
			printf_error(RED" -- Unexpected token '%s' --\n"RST, (*curr)->str);
			return (false);
		}
	}
	return (true);
}
