/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:16:54 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/08 12:21:24 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"
#include <unistd.h>

int	write_fd(char c, int fd)
{
	return (write(fd, &c, sizeof(char)));
}

void	write_str_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
		write_fd(str[i++], fd);
}
