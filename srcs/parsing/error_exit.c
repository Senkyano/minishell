/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:02:49 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/12 17:43:39 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

void	gestion_exit(char *msg, t_shell *bash)
{
	printf_error(CY"Minishell >: "RED"%s\n"RST, msg);
	if (bash->path)
		lib_free_split(bash->path);
	exit(0);
}
