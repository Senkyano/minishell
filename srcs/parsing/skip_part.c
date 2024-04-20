/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:00 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/20 12:24:54 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

int	skip_not_env(char *str, t_token *token)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		i++;
	else if (str[i] == '"')
		i++;
	while (str[i] && (str[i] != '$' || token->in_sgquote))
	{
		in_sgquote(str[i], token);
		in_doquote(str[i], token);
		i++;
	}
	return (i);
}

int	name_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (is_char(str[i]) || is_num(str[i])))
		i++;
	return (i);
}

int	skip_char(char *str)
{
	int		i;
	t_token	token;

	i = 0;
	lib_memset(&token, 0, sizeof(token));
	while (str[i] && (str[i] != 32 && str[i] != 11))
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (token.in_doquote || token.in_sgquote)
		{
			i++;
			while ((token.in_doquote || token.in_sgquote) && str[i])
			{
				in_doquote(str[i], &token);
				in_sgquote(str[i], &token);
				i++;
			}
		}
		else
			i++;
	}
	return (i);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 11 || str[i] == 9))
		i++;
	return (i);
}
