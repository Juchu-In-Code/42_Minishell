/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:06 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 18:21:20 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

void cleanup(t_shell *shell)
{
	if(shell->env->head)
		list_free(shell->env, free_env_entry);
	if(shell->tokens)
		list_free(shell->tokens, NULL);
	return;
}
