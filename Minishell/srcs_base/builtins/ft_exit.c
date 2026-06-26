/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/25 12:11:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

int	ft_exit(int ac, char **av, t_shell *shell)
{
	if (ac == 1)
	{
		shell->is_active = false;
		return (shell->last_exit_code);
	}
	if (ft_is_str_numeric(av[1]) == false)
	{
		ft_fprintf(2, E_MS" exit: %s: numeric argument required\n",
			av[1]);
		shell->is_active = false;
		return (2);
	}
	if (ac > 2)
	{
		ft_fprintf(2, E_MS" exit: too many arguments\n");
		return (1);
	}
	shell->is_active = false;
	return (ft_atol(av[1]));
}
