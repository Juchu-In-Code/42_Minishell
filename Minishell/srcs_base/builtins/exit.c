/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/03 14:36:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void	ft_exit(int ac, char **av, t_shell* shell)
{
	ft_fprintf(1, "exit\n");
	
	//excludes case where we have no args first
	if(ac == 1)
	{
		//should exit with the last program exit code
		shell->is_active = false;
		return;
	}

	//if this line is reached it means av[1] exists
	if(ft_is_str_numeric(av[1]) == false)
	{
		//should actually exit but indicate "arg is not numeric"
		ft_fprintf(2, "minishell: exit: %s numeric argument required\n", av[1]);
		shell->last_exit_code = 2;
		shell->is_active = false;
		return;
	}

	if(ac > 2)
	{
		//shouldn't exit and indicate too many args
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		shell->last_exit_code = 1;
		return;
	}
	
	//last_exit_code var is an unsigned char -> used for simple and correct conversion to 0-255 value from an int
	shell->last_exit_code = (unsigned char)ft_atol(av[1]);
	shell->is_active = false;
}