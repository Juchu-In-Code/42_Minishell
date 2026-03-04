/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 16:29:51 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

bool	line_to_env(t_shell *shell, char *line)
{
	t_env	*entry;

	// TODO:
		// si ya existe...
		// modify it( + check append mode)
	// otra opción es pasar el modo como un 3er arg
	// si no existe antes pero append está seteado, se crea normal
	entry = line_to_dict_entry(line);
	if (!entry)
		return (false);
	list_insert_tail(shell->env, entry);
	return (true);
}
