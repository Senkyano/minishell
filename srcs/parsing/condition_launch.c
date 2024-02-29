/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:05:03 by rihoy             #+#    #+#             */
/*   Updated: 2024/02/29 18:26:00 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../utils/lib_utils.h"

void	launch_shell(int argc, const char **env)
{
	if (argc != 1)
	{
		print_error("MINISHELL >: 'argument not require'");
		exit(0);
	}
	if (!env | !env[0])
	{
		print_error("MINISHELL >: 'environement require'");
		exit(0);
	}
}
