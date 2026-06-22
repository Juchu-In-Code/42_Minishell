/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 13:15:54 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"

extern int g_sigexit;

bool	setup(t_shell *shell, char **env)
{
	g_sigexit = 0;

	if (!clone_env(shell, env))
		return(false);
	shell->bkstd[IN] = dup(IN);
	shell->bkstd[OUT] = dup(OUT);
	shell->bkstd[ERR] = dup(ERR);
	shell->is_active = true;
	shell->last_exit_code = 0;
	return (true);
}
