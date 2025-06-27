/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:57:34 by jgalizio          #+#    #+#             */
/*   Updated: 2025/04/23 16:03:06 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	func_caller_fd(va_list args, const char *str, ssize_t fd)
{
	size_t	len;

	len = 0;
	if (*str == '%')
		len += ft_putchar_fd('%', fd);
	else if (*str == 'c')
		len += ft_putchar_fd((char)va_arg(args, int), fd);
	else if (*str == 's')
		len += ft_putstr_fd(va_arg(args, char *), fd);
	else if (*str == 'i' || *str == 'd')
		len += ft_putnbr_fd(va_arg(args, int), fd);
	else if (*str == 'u')
		len += ft_putunbr_fd(va_arg(args, unsigned int), fd);
	else if (*str == 'x')
		len += ft_puthex_fd(va_arg(args, unsigned int), *str, fd);
	else if (*str == 'X')
		len += ft_puthex_fd(va_arg(args, unsigned int), *str, fd);
	else if (*str == 'p')
		len += ft_putmemaddr_fd(va_arg(args, void *), fd);
	else
		return (0);
	return (len);
}

int	ft_fprintf(ssize_t fd, const char *str, ...)
{
	size_t	printed_total;
	va_list	args;

	printed_total = 0;
	va_start(args, str);
	if (!str || !*str)
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str)
				printed_total += func_caller_fd(args, str, fd);
		}
		else
			printed_total += ft_putchar_fd(*str, fd);
		str++;
	}
	va_end(args);
	return (printed_total);
}

int	ft_printf(const char *str, ...)
{
	size_t	printed_total;
	va_list	args;

	printed_total = 0;
	va_start(args, str);
	if (!str || !*str)
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str)
				printed_total += func_caller_fd(args, str, 1);
		}
		else
			printed_total += ft_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (printed_total);
}
