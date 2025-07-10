/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_indicator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:07:10 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/10 16:09:31 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	put_char_range(char c, int len, char *color)
{
	if (!color)
		while (len--)
			printf("%c", c);
	else
		while (len--)
			printf("%s%c"ANS_RES, color, c);
}

void	put_debug_indicator(char *input, int start, int len)
{
	printf("%s\n", input);
	put_char_range(' ', start, NULL);
	put_char_range('^', len, ANS_R);
}
