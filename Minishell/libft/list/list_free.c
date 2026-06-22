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

void	list_free(t_list *list, t_free free_func)
{
	t_item	*current;
	t_item	*next;

	if (!list)
		return;
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
				free(current->data);
				current->data = NULL;
			}
		}
		free(current);
		current = next;
	}
	free(list);
	list = NULL;
}
