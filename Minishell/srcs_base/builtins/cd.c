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

/*NOTE: dir_path (get_path function parameter) has to be dynamically allocated 
 * to enter into env list as an allocated char * so in case of incorrect
 * directory we have to free dir_path
 */

char	*get_path(char *dir_path, t_list *env)
{
	char	*tmp;

	if (!dir_path)
	{
		tmp = ft_strdup(get_env_val(env, "HOME"));
		if (!tmp)
		{
			printf("No HOME env var found");
			return (NULL);
		}
		chdir(tmp);
		return (tmp);
	}
	else if (chdir(dir_path) != 0)
	{
		perror("minishell: cd");
		if (dir_path)
			free(dir_path);
		return (NULL);
	}
	return (getcwd(NULL, 0));
}

int	cd(t_list *env, int ac, char **av)
{
	char	*dir_path;
	char	*tmp;
	t_env	*entr;

	if (ac > 2)
		printf("minishell: cd: too many arguments\n");
	if (ac > 2)
		return (1);
	tmp = ft_strdup(get_env_val(env, "PWD"));
	if (!tmp)
	{
		entr = create_dict_entry(ft_strdup("PWD"), getcwd(NULL, 0), 1);
		list_insert_tail(env, entr);
	}
	dir_path = get_path(av[1], env);
	if (!dir_path)
		return (1);
	if (!get_env(env, "OLDPWD"))
	{
		entr = create_dict_entry(ft_strdup("OLDPWD"), ft_strdup(""), 1);
		list_insert_tail(env, entr);
	}
	change_env_value(get_env(env, "OLDPWD"), tmp);
	change_env_value(get_env(env, "PWD"), dir_path);
	return (0);
}
