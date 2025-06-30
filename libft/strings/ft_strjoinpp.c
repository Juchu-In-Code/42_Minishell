/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinpp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:55:51 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/30 10:56:47 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoinpp(char **arr)
{
	size_t	total_len;
	char	*return_str;
	char	**tmp;

	if (!arr)
		return (NULL);
	tmp = arr;
	total_len = 1;
	while (*tmp != NULL)
	{
		total_len += ft_strlen(*tmp);
		tmp++;
	}
	return_str = ft_calloc(total_len, sizeof(char));
	tmp = arr;
	while (*tmp != NULL)
	{
		ft_strlcat(return_str, *tmp, total_len);
		tmp++;
	}
	return (return_str);
}
