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
		
		//it's a boolean function (true on detected builtin)	
		exec_builtin(ac, av, shell);

		free(input);
		input = NULL;
	}
}
