/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 12:09:43 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

// setupsubshell
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

bool	setup(t_shell *shell, char **env)
{
	if (!clone_env(shell, env))
		return(false);
	// add custom envs
	// setup quickaccess
	// setup segmented path
	// signal handler
	signal_setup();
	shell->bkstd[IN] = dup(IN);
	shell->bkstd[OUT] = dup(OUT);
	shell->bkstd[ERR] = dup(ERR);
	// bk other stuff
	tcgetattr(IN, &shell->termios);
	// heredoc id
	return (true);
}
