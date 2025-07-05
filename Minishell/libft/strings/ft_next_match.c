/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:10:22 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 17:10:35 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_next_match(char *str, int char_to_find)
{
	char	*pos_found;

	pos_found = ft_strchr(str, char_to_find);
	if (!pos_found)
		return (-1);
	return (pos_found - str);
}
