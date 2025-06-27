/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:57:14 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/16 18:46:38 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux_s;
	unsigned char	aux_c;
	size_t			i;

	aux_s = (unsigned char *)s;
	aux_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (aux_s[i] == aux_c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
