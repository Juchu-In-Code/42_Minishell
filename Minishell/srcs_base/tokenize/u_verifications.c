/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_verifications.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/12 19:00:37 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

bool	is_redir(t_tokt t)
{
	return (t == id_input || t == id_hdoc || t == id_output || t == id_append);
}

bool	is_quoted(t_tokt t)
{
	return (t == id_qdob || t == id_qsin);
}
