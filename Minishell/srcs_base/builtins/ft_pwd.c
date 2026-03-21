/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/03 14:36:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

int ft_pwd(int ac, char **av, t_shell *shell)
{
	char	*cwd;

	(void)ac;
	(void)av;
	(void)shell;
	
	cwd = malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
