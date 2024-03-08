/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:36:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/08 17:55:53 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

int	skip_space(char *str);

int	count_minishell(char *str)
{
	int		mini_count;
	t_token	token;
	int		i;

	i = 0;
	mini_count = 0;
	while (str[i])
	{
		if (!token.in_doquote)
			i += skip_space(str + i);
		in_doquote(str[i], &token);
		while (str[i] && token.in_doquote)
		{
			if (str[i] == '"')
				token.in_doquote = false;
			i++;
		}
		mini_count++;
		while (str[i] >= 'a' && str[i] <= 'z' && str[i])
			i++;
	}
	return (mini_count);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 11))
		i++;
	return (i);
}
