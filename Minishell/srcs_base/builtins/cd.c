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

static char    *ft_strlstchr(const char *s, char *until)
{
        char    *dup;
        size_t  len;

        len = ft_strlen(s) - 1;
        if (!s || !until)
                return (NULL);
        while (len > 0 && !ft_strchr(until, s[len]))
                len--;
        dup = ft_calloc(len + 1, sizeof(char));
        if (!dup)
                return (NULL);
        ft_strlcpy(dup, s, len + 1);
        return (dup);
}

static char *resolve_path(char **av, t_shell *shell)
{
	char *t;

	if(av[1] && av[1][0] == '/') //in case of absolute path;
		return (ft_strdup(av[1]));
	if(av[1] && av[1][0] == '-' && av[1][1] == '\0')
	{
        	if(!get_env(shell->env, "OLDPWD"))
		{
			printf("Can't find OLDPWD\n");
			return (NULL);
		}
		t = ft_strdup(get_env_val(shell->env, "OLDPWD"));
		printf("%s\n", t);
		return (t);
	}
	if(av[1] && ft_strncmp(av[1], "..", ft_strlen(av[1])) == 0)
	{
		char *val = get_env_val(shell->env, "PWD");
		t = ft_strlstchr(val, "/");
		if (!t)
			return(NULL);
		return(t);
	}
	else if(av[1])
	{
		t = ft_strjoinv(get_env_val(shell->env, "PWD"),"/",av[1],NULL); 
		if(!t)
			return (NULL);
		return(t);
	}
	return(ft_strdup(get_env_val(shell->env, "HOME")));
}

int	cd(t_shell *shell, int ac, char **av)
{
	char	*dir_path;
	char	*tmp;
	t_env	*entr;

	if(ac > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return(1);
	}
	dir_path = resolve_path(av, shell);
	if(chdir(dir_path) != 0)
	{
		perror("minishell: cd: ");
		free(dir_path);
		return (1);
	}
	if(!get_env(shell->env, "OLDPWD"))
	{
		entr = create_dict_entry(ft_strdup("OLDPWD"), ft_strdup(""), 1);
		list_insert_tail(shell->env, entr);
	}
	tmp = ft_strdup(get_env_val(shell->env, "PWD"));
	change_env_value(get_env(shell->env, "OLDPWD"), tmp);
	change_env_value(get_env(shell->env, "PWD"), dir_path);
	return (0);
}
