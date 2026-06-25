/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:07:26 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 13:16:11 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void	sig_interactive(int sig)
{
	(void)sig;
	g_sigexit = 130;
	write(STDOUT_FILENO, ANS_R"\n", sizeof(ANS_R"\n"));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_heredoc(int sig)
{
	(void)sig;
	g_sigexit = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	close(STDIN_FILENO);
}

void	set_signal(int signal, void (*sig_instruction)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_instruction;
	sigaction(signal, &sa, NULL);
}
