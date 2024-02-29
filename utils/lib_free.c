/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:00:54 by rihoy             #+#    #+#             */
/*   Updated: 2024/02/29 14:10:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"
#include <stdlib.h>

void	free_split(char **sent)
{
	size_t	i;

	i = 0;
	if (!sent)
		return ;
	while (sent[i])
		free(sent[i++]);
	free(sent);
}
