/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:11:53 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/18 14:36:02 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*extracted;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	while (i < len && s[start + i])
		i++;
	extracted = ft_calloc((i + 1), sizeof(char));
	if (!extracted)
		return (NULL);
	extracted[i] = 0;
	while (i--)
		extracted[i] = s[start + i];
	return (extracted);
}
