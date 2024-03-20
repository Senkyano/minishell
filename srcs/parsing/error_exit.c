/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:02:49 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/20 16:55:23 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	gestion_exit(char *msg, t_shell *bash)
{
	printf_error(CY"Minishell >: "RED"%s\n"RST, msg);
	if (bash->path)
		lib_free_split(bash->path);
	exit(0);
}
