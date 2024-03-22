/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:04:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/22 14:20:25 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void	choosing(char c, va_list lst, int *len);

int	printf_error(const char *str, ...)
{
	int		len;
	va_list	lst;

	va_start(lst, str);
	len = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			choosing(*str, lst, &len);
		}
		else
			len += write_fd(*str, 2);
		str++;
	}
	va_end(lst);
	return (len);
}

void	choosing(char c, va_list lst, int *len)
{
	if (c == 's')
		*len += print_error(va_arg(lst, char *));
	else if (c == 'd')
		*len += nbr_base(va_arg(lst, int), 10);
	else if (c == 'x')
		*len += nbr_base(va_arg(lst, int), 16);
	else if (c == 'c')
		*len += write_fd(va_arg(lst, int), 2);
}
