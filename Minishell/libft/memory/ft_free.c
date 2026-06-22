/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:31:28 by jgalizio          #+#    #+#             */
/*   Updated: 2024/12/19 14:36:36 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* Takes a &pointer to free it and sends it to NULL*/
void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	ptr = NULL;
}
