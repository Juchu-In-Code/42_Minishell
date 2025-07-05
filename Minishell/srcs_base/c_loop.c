/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/05 09:02:22 by jgalizio         ###   ########.fr       */
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

		if(ac)
		{
			//it's a boolean function (true on detected builtin)	
			if(!exec_builtin(ac, av, shell))
			{
				//line is heap allocated
				line = get_line_to_exec(av[0], shell->env);
				if(line)
				{
					
					printf("line: %s\n", line);
					free(line);
					shell->last_exit_code = 0;
				}
				else
				{
					ft_fprintf(2, "minishell: %s: No such file or directory\n", av[0]);
					shell->last_exit_code = 127;
				}
			}
		}
		
		ft_free_matrix((void *)av);
		free(input);
		input = NULL;
	}
}
