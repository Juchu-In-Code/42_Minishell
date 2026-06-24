/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:46:45 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 07:16:22 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	list_free(t_list **list_to_free, t_free free_func)
{
	t_list	*list;
	t_item	*current;
	t_item	*next;

	if (!list_to_free || !*list_to_free)
		return;
	list	= *list_to_free;
	current = list->head;
	while (current)
	{
		next = current->next;
		if (current->data)
		{
			if (free_func)
				free_func(current->data);
			else
			{
				ft_free((void**)&current->data);
				current->data = NULL;
			}
		}
		ft_free((void**)&current);
		current = next;
	}
	ft_free((void**)list_to_free);
}

