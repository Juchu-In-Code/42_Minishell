/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/03 14:36:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void    cd(t_shell *shell, int ac, char **av)
{
        char *dir_path;                                        
        char *tmp;                                                                                                         
                                                                                                                           
        if(ac > 2)                                                                                                         
                return((void)printf("minishell: cd: too many arguments\n"));                                               
        if(av[1])                                                                                                          
                dir_path = av[1];                                                                                          
        else                                                                                                               
                dir_path = get_env_val(shell->env, "HOME");
        if(chdir(dir_path) != 0)
                return((void)printf("minishell: cd: can't find path\n"));
        tmp = get_env_val(shell->env, "PWD");
        change_env_value(get_env(shell->env, "PWD"), dir_path);
        change_env_value(get_env(shell->env, "OLDPWD"), tmp);
}
