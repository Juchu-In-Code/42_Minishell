/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmemaddr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:31:47 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/06 14:59:34 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putmemaddr_fd(void *mem_addr, ssize_t fd)
{
	size_t	len;

	if (mem_addr == 0)
		return (ft_putstr_fd("(nil)", fd));
	len = 0;
	len += ft_putstr_fd("0x", fd);
	len += ft_puthex_fd((size_t)mem_addr, 'x', fd);
	return (len);
}
