/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:16:35 by jgalizio          #+#    #+#             */
/*   Updated: 2026/06/25 13:49:14 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	change_env_value(t_env *env, char *new_val, int update_state)
{
	ft_free((void **)&env->dict[VAL]);
	env->state = update_state;
	env->dict[VAL] = new_val;
}

void	append_env_value(t_env *env, char *new_val, int update_state)
{
	char	*aux_val;

	env->state = update_state;
	aux_val = env->dict[VAL];
	env->dict[VAL] = ft_strjoin(aux_val, new_val);
	ft_free((void **)&aux_val);
}
