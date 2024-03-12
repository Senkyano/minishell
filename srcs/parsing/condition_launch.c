/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:05:03 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/12 16:52:21 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

void	launch_shell(int argc, const char **env)
{
	if (argc != 1)
	{
		printf_error(CY"Minishell >: "RED"'argument not require'\n"RST);
		exit(0);
	}
	if (!env | !env[0])
	{
		printf_error(CY"Minishell >: "RED"'environement require'\n"RST);
		exit(0);
	}
	printf_error(BLK"Minishell by "PUR"Yrio "BLK"and"Y" Rihoy"RST"\n");
}
