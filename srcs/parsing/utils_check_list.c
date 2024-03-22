/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:30:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/22 15:21:08 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

bool	in_inverquote(char c, t_token *token, t_shell *bash);

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

bool	in_feature(t_infopars *curr, t_shell *bash)
{
	int		i;
	t_token	token;

	i = 0;
	lib_memset(&token, 0, sizeof(token));
	while (curr->str[i])
	{
		if (!in_inverquote(curr->str[i], &token, bash))
			return (false);
		i++;
	}
	if (curr->str[0] == ';' || curr->str[0] == '\\')
	{
		bash->exit_status = 2;
		printf_error(RED" -- Feature not include '%s' --\n", curr->str);
		return (false);
	}
	return (true);
}

bool	in_inverquote(char c, t_token *token, t_shell *bash)
{
	if (c == '`' && !token->in_sgquote)
	{
		printf_error(RED" -- Feature not include '%c' --\n", c);
		bash->exit_status = 2;
		return (false);
	}
	return (true);
}
