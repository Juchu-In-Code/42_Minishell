/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:47:50 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/19 21:02:40 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (n-- && (*s1 || *s2))
		{
			if (*(unsigned char *)s1 != *(unsigned char *)s2)
				return (*(unsigned char *)s1 - *(unsigned char *)s2);
			s1++;
			s2++;
		}
	}
	return (0);
}
