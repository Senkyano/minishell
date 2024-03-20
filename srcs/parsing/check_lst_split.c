/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lst_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:52:58 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 19:16:37 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_lst_split(t_shell *bash)
{
	t_infopars	*curr;
	t_token		token;

	curr = bash->lst_char;
	lib_memset(&token, 0, sizeof(token));
	while (curr)
	{
		if (!finish_quote(curr->str, &token) || !good_operator(curr->str) || \
		!after_operator(curr, curr->next))
			return (false);
		curr = curr->next;
	}
	return (true);
}
