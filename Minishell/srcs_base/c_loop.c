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
	bool	end;

	input = NULL;
	set_signal_interactive();
	while (shell->is_active )
	{

		end = ft_readline(shell, &input);
		if(!end)
		{
			printf("exit\n");
			exit(shell->last_exit_code);
		}
		if(g_sigexit)
		{
			shell->last_exit_code = g_sigexit;
			g_sigexit = 0;
		}
		tokenize(shell, input);
		if (*input && shell->degug_mode)
			debug_tokens(shell->tokens, input);
		if(token_syntax_checker(shell, shell->tokens, input))
			if (assemble_cmds(shell))
				execution_pipeline(shell, input);
		if (input)
			free(input);
		input = NULL;
		set_signal_interactive();
	}
}
