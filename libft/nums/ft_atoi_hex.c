/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:57:13 by jgalizio          #+#    #+#             */
/*   Updated: 2025/04/27 18:09:30 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

uint32_t	ft_atoi_hex(const char *str)
{
	uint32_t		result;
	size_t			i;

	i = 0;
	result = 0;
	if (!str || !*str)
		return (0);
	if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
		i = 2;
	if (i <= ft_strlen(str))
	{
		while (str[i] && ft_strchr("0123456789abcdefABCDEF", str[i]))
		{
			if (ft_isdigit(str[i]))
				result = result * 16 + (str[i] - '0');
			else if (ft_isalpha(str[i]))
				result = result * 16 + ft_tolower(str[i]) - ('a' - 10);
			else
				break ;
			i++;
		}
	}
	return (result);
}
