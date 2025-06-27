/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:46:45 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 14:38:47 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*list_create(void)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	if (!list)
		return (false);
	list->head = NULL;
	list->tail = NULL;
	list->control = NULL;
	list->size = 0;
	return (list);
}

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
	free(item);
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
	free(item);
	if (free_func)
	{
		free_func(data);
		return (NULL);
	}
	return (data);
}

void	list_free(t_list *list, t_free free_func)
{
	t_item	*current;
	t_item	*next;

	current = list->head;
	if (!list)
		return ;
	while (current)
	{
		next = current->next;
		if (free_func && current->data)
			free_func(current->data);
		free(current);
		current = next;
	}
	free(list);
}
