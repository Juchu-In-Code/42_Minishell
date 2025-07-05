/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:46:45 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 07:17:52 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	list_insert_tail(t_list *list, void *data)
{
	t_item	*new_item;

	new_item = ft_calloc(1, sizeof(t_item));
	if (!list || !data)
		return ;
	if (!new_item)
		return ;
	new_item->data = data;
	if (!list->size)
	{
		list->head = new_item;
		list->tail = new_item;
	}
	else
	{
		new_item->prev = list->tail;
		list->tail->next = new_item;
		list->tail = new_item;
	}
	list->size++;
}

void	list_insert_head(t_list *list, void *data)
{
	t_item	*new_item;

	new_item = ft_calloc(1, sizeof(t_item));
	if (!list || !data)
		return ;
	if (!new_item)
		return ;
	new_item->data = data;
	if (!list->size)
	{
		list->head = new_item;
		list->tail = new_item;
	}
	else
	{
		new_item->next = list->head;
		list->head->prev = new_item;
		list->head = new_item;
	}
	list->size++;
}
