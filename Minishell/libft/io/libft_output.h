/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_output.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:58:39 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/06 15:36:36 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_OUTPUT_H
# define LIBFT_OUTPUT_H

# include "../libft_incs.h"

int		ft_fprintf(ssize_t fd, const char *str, ...);
int		ft_printf(const char *str, ...);

int		ft_putchar_fd(char c, ssize_t fd);
int		ft_puthex_fd(size_t nbr, char c, ssize_t fd);
int		ft_putmemaddr_fd(void *mem_addr, ssize_t fd);
int		ft_putnbr_fd(int n, ssize_t fd);
int		ft_putstr_fd(char *str, ssize_t fd);
int		ft_putunbr_fd(unsigned int nbr, ssize_t fd);
void	ft_putendl_fd(char *s, int fd);

#endif
