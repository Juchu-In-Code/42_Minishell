/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_nums.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:07:23 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/06 15:39:00 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_NUMS_H
# define LIBFT_NUMS_H

# include "../libft_incs.h"

int			ft_atoi(const char *str);
long		ft_atol(const char *str);
uint32_t	ft_atoi_hex(const char *str);

size_t		ft_numlen(int nb);

#endif
