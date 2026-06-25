/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 12:57:01 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/25 13:17:54 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void	entry_helper(int state, t_env *entry, char **data)
{
	if (state == 1)
		change_env_value(entry, data[VAL], state);
	if (state == 2)
		append_env_value(entry, data[VAL], state);
	if (state == 2)
		free (data[VAL]);
	free (data[KEY]);
}
