/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:36:11 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/08 12:46:12 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"

int	nbr_base(long int nbr, int base)
{
	char	*bas;
	int		i;

	i = 0;
	bas = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr = -nbr;
		i += write_fd('-', 1);
	}
	if (nbr >= base)
		i += nbr_base(nbr / base, base);
	i += write_fd(bas[nbr % base], 1);
	return (i);
}
