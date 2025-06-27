/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:17 by jgalizio          #+#    #+#             */
/*   Updated: 2024/12/29 18:21:46 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, ssize_t fd)
{
	size_t	num;
	size_t	len;

	len = 0;
	num = n;
	if (n < 0)
	{
		num = (size_t)n * -1;
		len += ft_putchar_fd('-', fd);
	}
	if (num >= 10)
		len += ft_putnbr_fd(num / 10, fd);
	len += ft_putchar_fd(num % 10 + '0', fd);
	return (len);
}
