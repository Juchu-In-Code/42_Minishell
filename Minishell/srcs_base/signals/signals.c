/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:07:26 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 11:48:42 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"
#include <signal.h>

void signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1,"\n>>",3);
	else if(sig == SIGQUIT)
		write(1,"Do nothing",10);
//	else if(EOF)
//		exit_function;
}

void signal_setup()
{
	struct sigaction sa;
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
//	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(EOF, &sa, NULL);
}
