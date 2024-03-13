/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:00 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/13 17:20:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

int	skip_not_env(char *str)
{
	int	i;
	t_token	token;

	i = 0;
	lib_memset(&token, 0, sizeof(token));
	while ((str[i] != '$' || token.in_sgquote) && str[i])
	{
		in_sgquote(str[i], &token);
		i++;
	}
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
			while (token.in_doquote || token.in_sgquote)
			{
				i++;
				in_doquote(str[i], &token);
				in_sgquote(str[i], &token);
			}
		}
		i++;
	}
	return (i);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 11))
		i++;
	return (i);
}
