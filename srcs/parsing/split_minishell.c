/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:36:10 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/12 17:44:53 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
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
		if (str[i] != ' ' && str[i] != 11)
		{
			mini_str[nbr] = strup_to(str + i, skip_char(str + i));
			if (!mini_str[nbr++])
				return (lib_free_split(mini_str), NULL);
			i += skip_char(str + i);
		}
	}
	mini_str[nbr] = NULL;
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
		if (str[i] != ' ' && str[i] != 11)
			mini_count++;
		i += skip_char(str + i);
	}
	return (mini_count);
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
