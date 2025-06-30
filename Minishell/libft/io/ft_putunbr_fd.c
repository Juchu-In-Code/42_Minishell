/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:42 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/06 15:02:08 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putunbr_fd(unsigned int nbr, ssize_t fd)
{
	size_t	len;

	len = 0;
	if (nbr >= 10)
		len += ft_putunbr_fd(nbr / 10, fd);
	len += ft_putchar_fd(nbr % 10 + '0', fd);
	return (len);
}
