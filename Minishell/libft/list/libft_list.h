/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:03:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 07:20:07 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include "../libft_incs.h"

typedef struct s_item
{
	void			*data;
	struct s_item	*next;
	struct s_item	*prev;
}	t_item;

typedef struct s_list
{
	t_item	*head;
	t_item	*tail;
	void	*control;
	int32_t	size;
}	t_list;

typedef void	(*t_free)(void*);

t_list	*list_create(void *control);
void	list_insert_tail(t_list *list, void *data);
void	list_insert_head(t_list *list, void *data);
void	*list_remove_head(t_list *list, t_free free_func);
void	*list_remove_tail(t_list *list, t_free free_func);
void	list_free(t_list **list, t_free free_func);

#endif
