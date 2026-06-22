/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:20:14 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 17:17:13 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

char	*get_prompt(t_shell *shell)
{
	char *val;
	char *prompt;

	if (!shell->last_exit_code)
	{
		write (1, ANS_G, sizeof(ANS_G));
		return (ft_strdup(">> "ANS_RES));
	}
	else
	{
		val = ft_itoa(shell->last_exit_code);
		prompt = ft_strjoinv(ANS_R,val,">> ",ANS_RES, NULL);
		free (val);
		return (prompt);
	}
}

bool	ft_readline(t_shell *shell, char **buff)
{
	char *prompt;

	prompt = NULL;
	if (isatty(STDIN_FILENO))
	{
		prompt = get_prompt(shell);
		*buff = readline(prompt);
		if (prompt)
			free (prompt);
	}
	else
		*buff = get_next_line(STDIN_FILENO);
	if (!*buff)
		return (false);
	if (**buff)
		add_history(*buff);
	return(true);
}
