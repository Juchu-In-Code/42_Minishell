/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:20:14 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 17:17:13 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

bool	ft_readline(char **buff)
{
	// TODO:
		// hacer funcs de prompt
	*buff = readline(">> ");
	if (!*buff)
		return (false);
	if (**buff)
		add_history(*buff);
	//etc etc
	return(true);
}
