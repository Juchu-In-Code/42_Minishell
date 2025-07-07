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

static char *resolve_path(char **av, t_shell *shell)
{
	char *tmp;

	if(av[1] && av[1][0] == '/') //in case of absolute path;
		return (ft_strdup(av[1]));
	if(av[1] && av[1][0] == '-' && av[1][1] == '\0')
	{
        	if(!get_env(shell->env, "OLDPWD"))
			return (printf(":( Can't find  OLDPWD\n"), NULL);
		tmp = ft_strdup(get_env_val(shell->env, "OLDPWD"));
		printf("%s\n", tmp);
		return (tmp);
	}
	if(av[1])
	{
		tmp = get_env_val(shell->env, "PWD");
		tmp = ft_strjoinv(tmp,"/",av[1],NULL); 
		if(!tmp)
			return (printf("Bad join\n"), NULL);
		return(tmp);
	}
	return(ft_strdup(get_env_val(shell->env, "HOME")));
}

void    cd(t_shell *shell, int ac, char **av)
{
        char *dir_path;                                        
        char *tmp;                                                                                                         
                                                                                                                           
	if(ac > 2)                                                                                                         
		return((void)printf("minishell: cd: too many arguments\n"));                                               
	dir_path = resolve_path(av, shell);
	if(chdir(dir_path) != 0)
                return((void)perror("minishell: cd:"));
        if(!get_env(shell->env, "OLDPWD"))
                list_insert_tail(shell->env,create_dict_entry(ft_strdup("OLDPWD"),ft_strdup(""), 0));
        tmp = ft_strdup(get_env_val(shell->env, "PWD"));
        change_env_value(get_env(shell->env, "OLDPWD"), tmp);
        change_env_value(get_env(shell->env, "PWD"), dir_path);
}
