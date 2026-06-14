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

void	loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{

		tokenize(shell, input);
		if (*input)
			debug_tokens(shell->tokens, input);
		shell->pipe_count = token_syntax_checker(shell->tokens, input);
		assemble_cmds(shell);
		if(shell->cmds)
			execution_pipeline(shell, input);
		free(input);
		input = NULL;
	}
}
