/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detouch_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:48:29 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/17 21:48:34 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

static t_item	*get_list_item(t_list *list, char *key)
{
	t_item	*curr_node;
	t_env	*curr_env;

	if (!list || !key || !*key )
		return (NULL);
	curr_node = list->head;
	while (curr_node)
	{
		curr_env = curr_node->data;
		if (!ft_strcmp(curr_env->dict[KEY], key))
			return (curr_node);
		curr_node = curr_node->next;
	}
	return (NULL);
}

void	detach_env(t_list *list, char *key)
{
	t_item	*item;

	item = get_list_item(list, key);
	if (!list || !item)
		return ;
	if (item->prev)
		item->prev->next = item->next;
	else
		list->head = item->next;
	if (item->next)
		item->next->prev = item->prev;
	else
		list->tail = item->prev;
	list->size--;

	t_env *env = (t_env *)item->data;
	free(env->dict[KEY]);
	free(env->dict[VAL]);
	free(item->data);
	free(item);
}
