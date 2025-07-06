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
        {
                if(ft_strncmp(av[1],"/",1) == 0) //in case of absolute path;
                        dir_path = ft_strdup(av[1]);                                                                                     
                else
                {
                        tmp = get_env_val(shell->env, "PWD");
                        dir_path = ft_strjoinv(tmp,"/",av[1],NULL); 
			if(!dir_path)
                		return((void)printf("minishell: cd: bad malloc\n"));
                }
        }
        else                                                                                                               
                dir_path = ft_strdup(get_env_val(shell->env, "HOME"));
        if(chdir(dir_path) != 0)
                return((void)printf("minishell: cd: can't find path\n"));
        if(!get_env(shell->env, "OLDPWD"))
                list_insert_tail(shell->env,create_dict_entry(ft_strdup("OLDPWD"),ft_strdup(""), 0));
        tmp = ft_strdup(get_env_val(shell->env, "PWD"));
        change_env_value(get_env(shell->env, "OLDPWD"), tmp);
        change_env_value(get_env(shell->env, "PWD"), dir_path);
}
