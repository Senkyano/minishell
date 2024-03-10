/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:36:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/10 14:02:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

int	skip_space(char *str);
int	skip_char(char *str, t_token *token);

int	count_minishell(char *str)
{
	int		mini_count;
	t_token	token;
	int		i;

	i = 0;
	mini_count = 0;
	while (str[i])
	{
		i += skip_space(str + i);
		if (str[i] != " " || str[i] != 11)
			mini_count++;
		i += skip_char(str + i, &token);
	}
	return (mini_count);
}

int	skip_char(char *str, t_token *token)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != 32 && str[i] != 11))
	{
		in_doquote(str[i], token);
		in_sgquote(str[i], token);
		if (token->in_doquote || token->in_sgquote)
		{
			while (token->in_doquote || token->in_sgquote)
			{
				i++;
				in_doquote(str[i], token);
				in_sgquote(str[i], token);
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
