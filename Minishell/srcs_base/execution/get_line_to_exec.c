/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/26 14:13:33 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

static char	**get_paths(t_list *env, char *key)
{
	char	*raw_env;

	raw_env = get_env_val(env, key);
	if (!raw_env)
		return (NULL);
	return (ft_split(raw_env, ':'));
}

static char	**get_full_commands(char **paths, char *key)
{
	int		i;
	char	**full_commands;

	full_commands = ft_calloc(sizeof(char *), ft_count_arrays(paths));
	i = -1;
	while (paths[++i])
	{
		full_commands[i] = ft_strjoinv(paths[i], "/", key, NULL);
		if (!full_commands[i])
		{
			ft_free_matrix((void **)full_commands);
			return (NULL);
		}
	}
	full_commands[i] = NULL;
	return (full_commands);
}

static char	*access_check(char **access_options)
{
	int			i;
	struct stat	st;

	i = -1;
	while (access_options[++i])
	{
		if (access(access_options[i], X_OK) == 0
			&& stat(access_options[i], &st) == 0
			&& S_ISREG(st.st_mode))
		{
			//printf("Correct path found: %s\n", access_options[i]);
			return (ft_strdup(access_options[i]));
		}
	}
	return (NULL);
}

static char	*resolve_relative_path(char *key, t_list *env)
{
	char	**full_command_variants;
	char	**paths;
	char	*command_to_execute;

	paths = get_paths(env, "PATH");
	if (!paths)
	{
		printf("Corrupted PATH env variable\n");
		return (NULL);
	}
	full_command_variants = get_full_commands(paths, key);
	ft_free_matrix((void **)paths);
	if (!full_command_variants)
	{
		printf("Bad join\n");
		return (NULL);
	}
	command_to_execute = access_check(full_command_variants);
	ft_free_matrix((void **)full_command_variants);
	return (command_to_execute);
}

char	*get_line_to_exec(char *cmd, t_list *env)
{
	char	*command_to_execute;
	struct stat	st;

	if (!cmd || !*cmd)
		return (NULL);
	//if command string contains a '/'
	//it's probably an absolute path
	if(ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0 && stat(cmd, &st) == 0 && S_ISREG(st.st_mode))
			return(ft_strdup(cmd));
		return NULL;
	}

	command_to_execute = resolve_relative_path(cmd, env);
	if (command_to_execute != NULL)
		return command_to_execute;
	return (NULL);
}
