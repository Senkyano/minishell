/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:56:02 by yrio              #+#    #+#             */
/*   Updated: 2024/04/01 15:03:40 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

extern int	g_status_code;

void	sigint_handler(int signal)
{
	if (signal == 2)
	{
		if (g_status_code != IN_CMD)
			write(2, "^C\n", 3);
		else if (g_status_code == IN_CMD)
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			g_status_code = CTRL_C;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status_code = CTRL_C;
		(void)signal;
	}
}

void	sigquit_handler(int signal)
{
	if (signal == 3 && g_status_code == IN_CMD)
	{
		g_status_code = CTRL_BS;
		rl_replace_line("", 0);
		rl_redisplay();
		write(2, "Quit\n", 5);
		return ;
	}
}

void	init_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}
