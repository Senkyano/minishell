/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:05:03 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 21:54:46 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	launch_shell(int argc, const char **env)
{
	if (argc != 1)
	{
		printf_error(RED"'argument not require'\n"RST);
		exit(0);
	}
	if (!env | !env[0])
		printf_error(RED"'No Environement detected'\n"RST);
	printf_error(BLK"Minishell by "PUR"Yrio "BLK"and"Y" Rihoy"RST"\n");
}
