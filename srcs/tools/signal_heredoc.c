/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:18:12 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/20 14:07:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_here(int signal, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
    if (signal == 2)
    {
        write(0, "\n", 1);
        exit(130);
    }
}

void	init_signal_here(void)
{
    struct sigaction	act;
    
    act.sa_sigaction = sigint_handler_here;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &act, NULL) < 0)
        exit(1);
}
