/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:07:41 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 17:26:53 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

static bool	verify(int ac, char **av, char **env, t_shell *shell)
{
	if (ac == 2)
	{
		if(av[1][0] == '-' && av[1][1] == 'D')
			shell->debug_mode = true;
		else
			error_return(E_MS, E_DEBUG, false);
	}
	if (ac > 2)
			error_return(E_MS, E_ARG, false);
	if (!env || !*env)
			error_return(E_MS, E_ENV, false);
	return (true);
}

int g_sigexit;

int	main(int ac, char **av, char **env)
{
	static	t_shell	shell;

	if (!verify(ac, av, env, &shell))
		return (EXIT_FAILURE);
	setup(&shell, env);
	loop(&shell);
	cleanup(&shell);
	return (shell.last_exit_code);
}
