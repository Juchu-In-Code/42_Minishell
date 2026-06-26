/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/26 10:36:04 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	child_error_cleaner(t_shell *shell, char **env, char *path, int i)
{
	perror(shell->cmds[i].final_args[0]);
	ft_free_matrix((void**)env);
	child_cleanup(shell);
	ft_free((void**)&path);
	exit(126);
}

void	cleanup_exit(t_shell *shell, int status)
{
	child_cleanup(shell);
	exit(status);
}

