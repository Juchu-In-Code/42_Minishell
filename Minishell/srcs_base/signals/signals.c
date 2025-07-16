/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:07:26 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 13:16:11 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void signal_handler(int sig)
{
	(void)sig;
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
	write(1,"\n>> ",4);
}

void signal_setup()
{
	struct sigaction sa;
	struct sigaction si;

	sigemptyset(&sa.sa_mask);     // initialize mask to empty
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	si.sa_handler = SIG_IGN;	
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &si, NULL);
}

