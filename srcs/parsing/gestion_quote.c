/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:08:36 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/10 16:20:47 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	need_cutquote(char *str);
char		*without_quote(char *str, int len);

bool	suppress_quote(t_infopars *lst_char)
{
	t_infopars	*curr;
	int			len;
	char		*new_str;

	len = 0;
	curr = lst_char;
	while (curr)
	{
		if (need_cutquote(curr->str))
		{
			len = len_inquote(curr->str);
			new_str = without_quote(curr->str, len);
			if (!new_str)
				return (false);
			free(curr->str);
			curr->str = new_str;
		}
		curr = curr->next;
	}
	return (true);
}

char	*without_quote(char *str, int len)
{
	char	*new_str;
	int		i;
	int		j;
	t_token	token;
	t_token	trigger;

	lib_memset(&token, 0, sizeof(t_token));
	lib_memset(&trigger, 0, sizeof(t_token));
	i = -1;
	j = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (token.in_doquote != trigger.in_doquote || \
		token.in_sgquote != trigger.in_sgquote)
			trigger = token;
		else if (str[i])
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

static bool	need_cutquote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	len_inquote(char *str)
{
	int		i;
	t_token	token;
	t_token	trigger;
	int		len;

	len = 0;
	i = -1;
	lib_memset(&token, 0, sizeof(t_token));
	lib_memset(&trigger, 0, sizeof(t_token));
	while (str[++i])
	{
		in_doquote(str[i], &token);
		in_sgquote(str[i], &token);
		if (token.in_doquote != trigger.in_doquote || \
		token.in_sgquote != trigger.in_sgquote)
			trigger = token;
		else if (str[i])
			len++;
	}
	return (len);
}
