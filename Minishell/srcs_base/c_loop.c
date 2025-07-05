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
		__debug_tokens(shell->tokens, input);
		free(input);
		input = NULL;
	}
	// clean again?
}
