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
