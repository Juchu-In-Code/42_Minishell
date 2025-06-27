/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isempty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:31:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/04/15 20:52:56 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_bool	ft_str_isempty(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (t);
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (f);
	return (t);
}
