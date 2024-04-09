/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:08:36 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/09 22:12:57 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	suppress_quote(t_infopars *lst_char)
// {
// 	t_infopars	*curr;

// 	curr = lst_char;
// 	while (curr)
// 	{

// 		curr = curr->next;
// 	}
// }

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
		if (token.in_doquote != trigger.in_doquote && \
		token.in_sgquote != trigger.in_sgquote)
			trigger = token;
		else if (str[i])
			len++;
	}
	return (len);
}
