/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 18:57:09 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

// setupsubshell

bool	setup(t_shell *shell, char **env)
{
	if (!clone_env(shell, env))
		return(false);
	// add custom envs
	// setup quickaccess
	// setup segmented path
	// signal handler
	shell->bkstd[IN] = dup(IN);
	shell->bkstd[OUT] = dup(OUT);
	shell->bkstd[ERR] = dup(ERR);
	// bk other stuff
	tcgetattr(IN, &shell->termios);
	// heredoc id
	return (true);
}
