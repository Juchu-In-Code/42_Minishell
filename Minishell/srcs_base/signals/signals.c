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
	if(sig == SIGQUIT)
		return;
	else if (sig == SIGINT)
		write(1,"\n>> ",4);
//	else if(EOF)
//		exit_function;
}

void signal_setup()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));   // zero initialize the whole struct
	sigemptyset(&sa.sa_mask);     // initialize mask to empty
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(EOF, &sa, NULL);
}

