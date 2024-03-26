/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_list_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:54:41 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/26 20:12:48 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	finish_quote(char *str, t_token *token, t_shell *bash)
{
	int	i;

	i = 0;
	while (str[i])
	{
		in_doquote(str[i], token);
		in_sgquote(str[i], token);
		i++;
	}
	if (token->in_doquote || token->in_sgquote)
	{
		printf_error(RED" -- Unfinish quote --\n"RST);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}

bool	good_operator(char *str, t_shell *bash)
{
	if (is_operator(str[0]))
	{
		if (str_len(str) > 2)
		{
			bash->exit_status = 2;
			printf_error(RED" -- Unexpected Token '%s' --\n"RST, str);
			return (false);
		}
		if (str[0] == '&' && str_len(str) < 2)
		{
			bash->exit_status = 2;
			printf_error(RED" -- Unexpected Token '%s' --\n"RST, str);
			return (false);
		}
	}
	return (true);
}

bool	after_operator(t_infopars *pre, t_infopars *curr, t_infopars *next, \
t_shell *bash)
{
	if (pre)
	{
		if (is_operator(curr->str[0]) && is_redirection(pre->str[0]))
		{
			bash->exit_status = 2;
			printf_error(RED" -- Unexpected Token '%s' --\n"RST, curr->str);
			return (false);
		}
	}
	if (!is_operator(curr->str[0]))
		return (true);
	if (is_operator(curr->str[0]) && !next)
	{
		bash->exit_status = 2;
		printf_error(RED" -- Feature not include --\n"RST);
		printf_error("    Need command after '%s'\n", curr->str);
		return (false);
	}
	if (is_operator(curr->str[0]) && !is_operator(next->str[0]) && \
	next->str[0] != ')')
		return (true);
	bash->exit_status = 2;
	printf_error(RED" -- Unexpected Token '%s' --\n"RST, next->str);
	return (false);
}

bool	before_operator(t_infopars *curr, t_infopars *pre, t_shell *bash)
{
	if (is_operator(curr->str[0]) && !pre)
	{
		printf_error(RED" -- Unexpected Token '%s' --\n"RST, curr->str);
		printf_error("    Need command before '%s'\n", curr->str);
		bash->exit_status = 2;
		return (false);
	}
	if (is_operator(curr->str[0]) && is_operator(pre->str[0]))
	{
		printf_error(RED" -- Unexpected Token '%s' --\n"RST, curr->str);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}
