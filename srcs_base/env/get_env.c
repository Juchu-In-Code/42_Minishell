/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/08 21:12:03 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

t_env	*get_env(t_list *list, char *key)
{
	t_item	*curr_node;
	t_env	*curr_env;

	curr_node = list->head;
	while (curr_node)
	{
		curr_env = list->head->data;
		if (!ft_strcmp(curr_env->dict[KEY], key))
			return (curr_env);
		curr_node = curr_node->next;
	}
	return (NULL);
}

char	*get_env_val(t_list *list, char *key)
{
	t_env	*found_env;

	found_env = get_env(list, key);
	if (found_env)
		return (found_env->dict[VAL]);
	return (NULL);
}
