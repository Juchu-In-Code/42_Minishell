/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 17:00:01 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	print_env(t_list *list)
{
	t_item	*curr_node;
	t_env	*curr_env;

	curr_node = list->head;
	while (curr_node)
	{
		curr_env = curr_node->data;
		printf("%s=%s\n", curr_env->dict[KEY], curr_env->dict[VAL]);
		curr_node = curr_node->next;
	}
}
