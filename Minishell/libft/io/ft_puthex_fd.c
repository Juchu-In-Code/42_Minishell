/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:31:19 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/06 14:59:44 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex_fd(size_t nbr, char c, ssize_t fd)
{
	size_t	len;
	char	*lower;
	char	*upper;

	lower = "0123456789abcdef";
	upper = "0123456789ABCDEF";
	len = 0;
	if (nbr >= 16)
		len += ft_puthex_fd(nbr / 16, c, fd);
	if (c == 'x')
		len += ft_putchar_fd(lower[nbr % 16], fd);
	else if (c == 'X')
		len += ft_putchar_fd(upper[nbr % 16], fd);
	return (len);
}
