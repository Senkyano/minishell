/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:05:03 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/04 16:38:21 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

void	launch_shell(int argc, const char **env)
{
	if (argc != 2)
	{
		printf(CY"Minishell >: "RED"'argument not require'\n"RST);
		exit(0);
	}
	if (!env | !env[0])
	{
		printf(CY"Minishell >: "RED"'environement require'\n"RST);
		exit(0);
	}
	printf(BLK"Minishell by "PUR"Yrio "BLK"and"Y" Rihoy"RST"\n");
}
