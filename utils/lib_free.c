/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:00:54 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/02 17:23:34 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"
#include <stdlib.h>
#include <stdio.h>

void	lib_free_split(char **sent)
{
	size_t	i;

	i = 0;
	if (!sent)
		return ;
	while (sent[i])
 		free(sent[i++]);
	free(sent);
}
