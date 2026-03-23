/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/12 21:18:56 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

void	loop(t_shell *shell)
{
	char	*input;
	char	*line;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{
		char **av = ft_split(input, ' ');
		int ac = ft_get_array_length(av);
		
		//it's a boolean function (true on detected builtin)	
		if(!exec_builtin(ac, av, shell))
		{
			//line is heap allocated
			line = get_line_to_exec(av[0], shell->env);
			if(line)
			{
				printf("line: %s\n", line);
				free(line);
			}
			else
				printf("executable not found\n");
		}
		free(input);
		input = NULL;
	}
}
