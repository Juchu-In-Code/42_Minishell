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

bool exec_builtin(int ac, char **av, t_shell *shell)
{
	if(!av || !*av || av[0] == NULL ||ft_strlen(av[0]) == 0)
	{
		printf("Bad things happened\n");
		return false; 
	}
	
	printf("av[0] = %s\n", av[0]);
	if(!ft_strcmp(av[0], "echo"))
		echo(ac, av);
	else if(!ft_strcmp(av[0], "cd"))
		cd(shell->env, ac, av);
	else if(!ft_strcmp(av[0], "pwd"))
		pwd();
	else if(!ft_strcmp(av[0], "export"))
	{
		//int	export(char **av, t_shell *shell)
		export(&av[1], shell);
		//this export implementation only accepts its arguments
		//"export" with export(av, shell) actually gets parsed as 
		//export export. -> so i send it args from the (&av[1]) so the
		//first av gets omited and function works as intended
	}
	else if(!ft_strcmp(av[0], "env"))
		ft_env(ac, shell->env);
	else if(!ft_strcmp(av[0], "unset"))
		detach_env(shell->env, av[1]);
	else if(!ft_strcmp(av[0], "exit"))
		ft_exit(ac, av, shell);
	
	return true;
}

void	loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{
		// signals
		// tokenize
		// process and expand
		//		manage subshells...
		//		redirects + pipes
		//		forks + execute
		// clean
		char **av = ft_split(input, ' ');
		int ac = ft_get_array_length(av);
		
		exec_builtin(ac, av, shell);
		printf("shell state: %b\n", shell->is_active);

		free(input);
		input = NULL;
	}
}
