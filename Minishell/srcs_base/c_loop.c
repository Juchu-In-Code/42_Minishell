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

/*
char *get_path(char *dir_path, t_list *env)
{
	char *tmp;
	if(!dir_path)
	{
		tmp = ft_strdup(get_env_val(env, "HOME"));
		if(!tmp)
		{
			printf("No HOME env var found");
			return(NULL);
		}
		return(ft_strdup(get_env_val(env, "HOME")));
	}
	if(chdir(dir_path) != 0)
	{
		perror("minishell: cd: ");
		//free(dir_path);
		return (NULL);
	}
	return (getcwd(NULL, 0));
}

int	cd(t_list *env, int ac, char **av)
{
	char	*dir_path;
	char	*tmp;
	t_env	*entr;

	if(ac > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return(1);
	}
	tmp = ft_strdup(get_env_val(env, "PWD"));
	if(!tmp)
	{
		entr = create_dict_entry(ft_strdup("PWD"), getcwd(NULL, 0) , 1);
		list_insert_tail(env, entr);
	}
	dir_path = get_path(av[1], env);
	if(!get_env(env, "OLDPWD"))
	{
		entr = create_dict_entry(ft_strdup("OLDPWD"), ft_strdup(""), 1);
		list_insert_tail(env, entr);
	}
	change_env_value(get_env(env, "OLDPWD"), tmp);
	change_env_value(get_env(env, "PWD"), dir_path);
	return (0);
}
*/
void	loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (ft_readline(&input)) // o usar una constante o !should_exit
	{
		// signals
		// tokenize
		// process and expand
		//		manage subshells...
		//		redirects + pipes
		//		forks + execute
		// clean
		tokenize(shell, input);
		if (*input)
			debug_tokens(shell->tokens, input);
		token_syntax_checker(shell->tokens, input);
		free(input);
		input = NULL;
	}
	// clean again?
}
