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
        t_env *env_node;
        char *dir_path;
        char *tmp;

        if(ac > 2)
                printf("minishell: cd: too many arguments\n");
        if(av[1])
                dir_path =ft_strdup(av[1]);
        else
                dir_path = ft_strdup(get_env_val(shell->env, "HOME"));
        if(chdir(dir_path) != 0) //0 is success in case of chdir func
                return((void)printf("Cant find path\n"));
        tmp = ft_strdup(get_env_val(shell->env, "PWD"));
        env_node = get_env(shell->env, "PWD");
        change_env_value(env_node, dir_path);
        char *debug = get_env_val(shell->env, "PWD");
        printf("%s\n", debug);
        env_node = get_env(shell->env, "OLDPWD");
        change_env_value(env_node, tmp);
        free(dir_path);
        free(tmp);
}
