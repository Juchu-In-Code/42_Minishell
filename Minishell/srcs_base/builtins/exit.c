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
#include <stdio.h>

int	ft_exit(int ac, char **av)
{
	if(ac > 2)
	{
		//shouldn't exit and indicate too many args
		printf("exit\nminishell: exit: too many arguments\n");
		return 127;
	}
	
	//excludes case where we have no args first
	if(!av[1])
	{
		printf("exit\n");
		return 0;
	}

	//if this line is reached it means av[1] exists
	if(!ft_is_str_numeric(av[1]))
	{
		//should actually exit but indicate "arg is not numeric"
		printf("exit\nminishell: exit: arg is not numeric\n");
		return 2;
	}
	unsigned char ans = ft_atoi(av[1]);	
	printf("exit\n");
	printf("debug: exit code %d\n", ans);
	return(ans);
}