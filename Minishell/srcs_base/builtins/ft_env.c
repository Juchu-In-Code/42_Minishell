/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/03 14:36:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"

int ft_env(int ac, t_list *env)
{
    if(ac > 1)	
    {
    	ft_fprintf(2, "minishell: env: too many arguments\n");
        return 1;
	}

	print_env(env);
    return 0;
}