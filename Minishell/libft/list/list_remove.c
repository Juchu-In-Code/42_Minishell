/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:46:45 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 07:18:18 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*list_remove_head(t_list *list, t_free free_func)
{
	t_item	*item;
	void	*data;

	item = list->head;
	data = item->data;
	if (!list || list->size == 0)
		return (NULL);
	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = item->next;
		list->head->prev = NULL;
	}
	list->size--;
	ft_free((void**)&item);
	if (free_func)
	{
		free_func(data);
		return (NULL);
	}
	return (data);
}

void	*list_remove_tail(t_list *list, t_free free_func)
{
	void	*data;
	t_item	*item;

	if (!list || !list->size)
		return (NULL);
	item = list->tail;
	data = item->data;
	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->tail = item->prev;
		list->tail->next = NULL;
	}
	list->size--;
	ft_free((void**)&item);
	if (free_func)
	{
		free_func(data);
		return (NULL);
	}
	return (data);
}
