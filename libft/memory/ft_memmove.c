/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:40:58 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/18 14:23:13 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*aux_dest;
	const unsigned char	*aux_src;

	if (!dest && !src)
		return (NULL);
	if (n == 0 || dest == src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	aux_dest = (unsigned char *)dest + n;
	aux_src = (const unsigned char *)src + n;
	while (n--)
		*--aux_dest = *--aux_src;
	return (dest);
}
