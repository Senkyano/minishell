/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:08:36 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/09 21:11:25 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	suppress_quote(t_infopars *lst_char)
{
	t_infopars	*curr;

	curr = lst_char;
	while (curr)
	{

		curr = curr->next;
	}
}
