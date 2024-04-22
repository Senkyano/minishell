/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:56:02 by yrio              #+#    #+#             */
/*   Updated: 2024/04/22 13:53:55 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == 2)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	manage_signal(int status, int exit_status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		if (g_status_code != CTRL_BS)
		{
			write(1, "Quit (core dumped)\n", 20);
			g_status_code = CTRL_BS;
		}
		exit_status = 131;
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (g_status_code != CTRL_C)
		{
			write(1, "\n", 1);
			g_status_code = CTRL_C;
		}
		exit_status = 130;
	}
	return (exit_status);
}
