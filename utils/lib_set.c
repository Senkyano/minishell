/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:32:00 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/05 15:36:52 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"

void	*lib_memset(void *pt, int value, size_t stats)
{
	char	*init;

	init = pt;
	while (stats > 0)
	{
		init[stats - 1] = (unsigned char)value;
		stats--;
	}
	return (init);
}
