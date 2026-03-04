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

bool exec_builtin(int ac, char **av, t_shell *shell, t_list *env)
{
	if(!av || !*av || av[0] == NULL ||ft_strlen(av[0]) == 0)
	{
		printf("Bad things happened\n");
		return false; 
	}
	
	printf("av[0] = %s\n", av[0]);
	if(!ft_strcmp(av[0], "echo"))
	{
		//int	echo(int argc, char **argv)
		printf("echo detected\n");
		echo(ac, av);
	}
	else if(!ft_strcmp(av[0], "cd"))
	{
		printf("cd detected\n");
		//int	cd(t_list *env, int ac, char **av)
		cd(env, ac, av);
	}
	else if(!ft_strcmp(av[0], "pwd"))
	{
		printf("pwd detected\n");
		pwd();
	}
	else if(!ft_strcmp(av[0], "export"))
	{
		//int	export(char **av, t_shell *shell)
		printf("detected export\n");
		export(&av[1], shell);
		//this export implementation only accepts its arguments
		//"export" with export(av, shell) actually gets parsed as 
		//export export. -> so i send it args from the (&av[1]) so the
		//first av gets omited and function works as intended
	}
/*	else if(!ft_strcmp(av[0], "unset"))
		//unset();
	else if(!ft_strcmp(av[0], "env"))
		//env();
	else if(!ft_strcmp(av[0], "exit"))
		//exit();*/
	else
		return false;

	return true;
}

void	loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (ft_readline(&input))
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
		
		exec_builtin(ac, av, shell, shell->env);

		free(input);
		input = NULL;
	}
}
