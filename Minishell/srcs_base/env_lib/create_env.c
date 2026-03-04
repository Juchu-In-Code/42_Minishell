/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 07:28:14 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

// NOTE: Both key and val must be heap allocated
t_env	*create_dict_entry(char *key, char *val, int state)
{
	t_env	*entry;

	if (!key || !val)
		return (NULL);
	entry = ft_calloc(1, sizeof(t_env));
	if (!entry)
		return (NULL);
	entry->dict[KEY] = key;
	entry->dict[VAL] = val;
	entry->state = state;
	return (entry);
}

t_env	*line_to_dict_entry(char *line)
{
	t_env	*entry;
	char	*sep;
	char	*key;
	uint8_t	state;

	if (!line)
		return (NULL);
	state = 0;
	sep = ft_strchr(line, '=');
	key = ft_strunt(line, "=");
	if (!sep || !key)
		return (NULL);
	// TODO:
	//	que pasa si ya existe de antes?
	// if (matches_ql(key))
	// 	state = 1;
	entry = create_dict_entry(key, ft_strdup(sep + 1), state);
	return (entry);
}

bool	clone_env(t_shell *shell, char **env)
{
	t_env	*entry;
	int		i;

	shell->env = list_create(NULL);
	if (!shell->env)
		return (false);
	if (!env || !*env)
		return (false);
	i = 1;
	while (env && env[i])
	{
		entry = line_to_dict_entry(env[i]);
		if (!entry)
			return (false);
		list_insert_tail(shell->env, entry);
		i++;
	}
	return (true);
}
