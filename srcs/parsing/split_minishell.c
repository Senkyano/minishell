/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:36:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/20 14:24:15 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

int	skip_space(char *str);
int	skip_char(char *str);

char	**split_minishell(char *str)
{
	char	**mini_str;
	int		i;
	int		nbr;

	mini_str = malloc(sizeof(char *) * (count_minishell(str) + 1));
	if (!mini_str)
		return (NULL);
	i = 0;
	nbr = 0;
	while (str[i])
	{
		i += skip_space(str + i);
		if (str[i] != ' ' && str[i] != 9)
		{
			mini_str[nbr] = strup_to(str + i, skip_char(str + i));
			if (!mini_str[nbr++])
				return (lib_free_split(mini_str), NULL);
			i += skip_char(str + i);
		}
	}
	mini_str[nbr] = NULL;
	free(str);
	return (mini_str);
}

int	count_minishell(char *str)
{
	int		mini_count;
	int		i;

	i = 0;
	mini_count = 0;
	while (str[i])
	{
		i += skip_space(str + i);
		if (str[i] != ' ' && str[i] != 9)
			mini_count++;
		i += skip_char(str + i);
	}
	return (mini_count);
}

bool	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != 9 && str[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
