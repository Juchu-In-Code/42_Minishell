/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/30 11:12:22 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

static bool	is_dash_n(char *str, char n)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != n)
			return (false);
		i++;
	}
	return (true);
}

int	echo(int argc, char **argv)
{
	bool	no_new_line;
	int		index;

	no_new_line = false;
	index = 1;
	while (index < argc && is_dash_n(argv[index], 'n') == true)
	{
		index++;
		no_new_line = true;
	}
	while (index < argc)
	{
		printf("%s", argv[index]);
		index++;
		if (index != argc)
			printf(" ");
	}
	if (no_new_line == false)
		printf("\n");
	return (0);
}
