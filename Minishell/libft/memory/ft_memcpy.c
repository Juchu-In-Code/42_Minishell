/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:40:58 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/16 18:46:34 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*aux_src;
	char		*aux_dest;

	if (dest != src && n != 0)
	{
		aux_dest = (char *)dest;
		aux_src = (const char *)src;
		while (n--)
			*aux_dest++ = *aux_src++;
	}
	return (dest);
}
