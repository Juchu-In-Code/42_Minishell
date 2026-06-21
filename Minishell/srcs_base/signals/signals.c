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

extern int g_sigexit;

static void	sig_interactive(int sig)
{
	(void)sig;
	g_sigexit = 130;
	write(STDOUT_FILENO, ANS_R"\n", 7);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_heredoc(int sig)
{
	(void)sig;
	g_sigexit = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	close(STDIN_FILENO);
}

static void	set_signal(int signal, void (*sig_instruction)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_instruction;
	sigaction(signal, &sa, NULL);
}

void	set_signal_parent(void)
{
	set_signal(SIGINT, SIG_IGN);
	set_signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child(void)
{
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void) 
{
	set_signal(SIGINT, sig_heredoc);
	set_signal(SIGQUIT, SIG_IGN);
}

void	set_signal_interactive(void) 
{
	set_signal(SIGINT, sig_interactive);
	set_signal(SIGQUIT, SIG_IGN);
}
