/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:16:35 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/09 17:26:36 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	change_env_value(t_env *env, char *new_val, int update_state)
{
	free(env->dict[VAL]);
	env->state = update_state;
	env->dict[VAL] = new_val;
}

void	append_env_value(t_env *env, char *new_val, int update_state)
{
	char	*aux_val;

	env->state = update_state;
	aux_val = env->dict[VAL];
	env->dict[VAL] = ft_strjoin(aux_val, new_val);
	free(aux_val);
}
