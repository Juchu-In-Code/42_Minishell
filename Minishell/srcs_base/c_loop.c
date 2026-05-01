/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:57 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

void	execute(char *line, char **av, t_list *env)
{

	pid_t pid = fork(); 
	// Both child and parent will now start execution from here.
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
	}
	else if(pid == 0) 
	{
		//Child
		execve(line, av, env_list_to_ptr(env));
	}
	else 
	{
		// Parent process code goes here
		// Parent has to wait for childs
		wait(NULL);
	}
}

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
					execute(line, av, shell->env);
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
