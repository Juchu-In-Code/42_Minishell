/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/30 11:12:22 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void pwd()
{
	char *cwd;
	cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	free(cwd);
}
