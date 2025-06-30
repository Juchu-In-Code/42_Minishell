/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:31:38 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/30 11:01:42 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*strjoinv(const char *str, ...)
{
	char	*return_str;
	char	*tmp_str;
	size_t	size;
	va_list	args;
	va_list	tmp_args;

	if (!str)
		return (NULL);
	va_start(args, str);
	va_copy(tmp_args, args);
	size = ft_strlen(str) + ft_strlenv(tmp_args) + 1;
	return_str = ft_calloc(size, sizeof(char));
	ft_strlcpy(return_str, str, size);
	tmp_str = va_arg(args, char *);
	while (tmp_str)
	{
		ft_strlcat(return_str, tmp_str, size);
		tmp_str = va_arg(args, char *);
	}
	va_end(args);
	va_end(tmp_args);
	return (return_str);
}
