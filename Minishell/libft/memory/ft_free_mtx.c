/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:16:41 by jgalizio          #+#    #+#             */
/*   Updated: 2024/12/19 14:39:13 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_matrix(void **mtx)
{
	size_t	i;

	i = -1;
	while (mtx[++i])
		ft_free(&mtx[i]);
	free(mtx);
	mtx = NULL;
}
