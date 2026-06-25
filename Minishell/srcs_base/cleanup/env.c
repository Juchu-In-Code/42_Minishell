/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:06 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 18:21:20 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void free_env_entry(void *env_entry)
{
	t_env	*entry;

	entry = (t_env*)env_entry;
	if(!entry)
		return;
	if(entry->dict[KEY])
	{
		ft_free((void**)&entry->dict[KEY]);
		entry->dict[KEY] = NULL;
	}
	if(entry->dict[VAL])
	{
		ft_free((void**)&entry->dict[VAL]);
		entry->dict[VAL] = NULL;
	}
	ft_free((void**)&entry);
}
