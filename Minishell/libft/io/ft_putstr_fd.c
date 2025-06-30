/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:29:55 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/06 15:01:37 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fd(char *str, ssize_t fd)
{
	size_t	len;

	len = 0;
	if (!str)
		return (ft_putstr_fd("(null)", fd));
	while (*str)
	{
		len += ft_putchar_fd(*str, fd);
		str++;
	}
	return (len);
}
