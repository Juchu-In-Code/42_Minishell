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

int main(int argc, char **argv)
{
	char	*path;
	if(argc > 2)
		printf("minishell: cd: too many arguments\n");
	if(argv[1]) //if 1st arg exists 
		path = ft_strdup(argv[1]);
	else
		path = ft_strdup(env_HOME); // store home env var into env_HOME
	if(chdir(path) != 0)
		exit_with_error("cant find path");
	
	//change PWD with path
	
	//modify the OLDPWD
	//change OLDPWD with CWD
	//so when we move to the PATH -> OLDPWD contains old working directory
	free(path);
}
