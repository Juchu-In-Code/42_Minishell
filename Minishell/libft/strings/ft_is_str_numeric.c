/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2024/12/29 18:03:31 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

bool	ft_is_str_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i = 1;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}
