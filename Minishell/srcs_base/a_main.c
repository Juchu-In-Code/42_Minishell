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
int g_sigexit = 0;

static bool	verify(int ac, char **av, char **env, t_shell *shell)
{
	if (ac == 2)
	{
		if(av[1][0] == '-' && av[1][1] == 'D')
			shell->degug_mode = true;
		else
		{
			printf(ANS_R"Minishell: Incorrect argument passed, use -D for debug mode."ANS_RES);
			return (false);
		}
	}
	if (ac > 2)
	{
		printf(ANS_R"Minishell: Too many arguments passed, use -D for debug mode."ANS_RES);
		return (false);
	}
	if (!env || !*env)
	{
		printf(ANS_R"Minishell: A correct set of environment variables must be provided."ANS_RES);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (!verify(ac, av, env, &shell))
		return (EXIT_FAILURE);
	setup(&shell, env);
	loop(&shell);
	cleanup(&shell);
	return (shell.last_exit_code);
}
