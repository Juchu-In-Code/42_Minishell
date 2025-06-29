/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:41:14 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/28 16:43:26 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

size_t	ft_strlenv(va_list args_copy)
{
	size_t	size;
	char	*tmp_str;

	size = 0;
	tmp_str = va_arg(args_copy, char *);
	while (tmp_str)
	{
		size += ft_strlen(tmp_str);
		tmp_str = va_arg(args_copy, char *);
	}
	return (size);
}
