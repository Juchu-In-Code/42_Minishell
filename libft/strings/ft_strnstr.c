/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:47:50 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/16 18:45:55 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i_big;
	size_t	i_lil;

	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	i_big = 0;
	while (big[i_big] && i_big < len)
	{
		i_lil = 0;
		while (big[i_big + i_lil] == little[i_lil] && i_big + i_lil < len)
		{
			i_lil++;
			if (!little[i_lil])
				return ((char *)&big[i_big]);
		}
		i_big++;
	}
	return (NULL);
}
