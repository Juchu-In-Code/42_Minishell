/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_interpreter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:04:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/12 21:23:11 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

bool	verify_token(t_tokt t, int *context)
{
	if (*context == 1)
	{
		*context = 0;
		if (t == id_pipe)
			return (false);
		if (is_redir(t))
			*context = 2;
		return (true);
	}
	if (*context == 2)
		if (!(t == id_string || is_quoted(t)))
			return (false);
	if (*context == 3 && (t == id_pipe || t == id_fin))
		return (false);
	*context = 0;
	if (t == id_pipe)
		*context = 3;
	if (is_redir(t))
		*context = 2;
	return (true);
}

static bool	syntax_error_handler(t_shell *shell, char *input, t_tok *token)
{
	printf(ANS_Y"\nMinishell:\n"ANS_RES);
	put_debug_indicator(input, token->pos, token->size);
	if (token->type != id_fin)
		printf(ANS_R" Unexpected token found, syntax error\n"ANS_RES);
	else
		printf(ANS_R"^ Unexpected end of line, syntax error\n"ANS_RES);
	shell->last_exit_code = 2;
	return (false);
}

bool	token_syntax_checker(t_shell *shell, t_list *token_list, char *input)
{
	t_item	*current;
	t_tok	*token;
	int		context;

	context = 1;
	shell->pipe_count = 0;
	current = token_list->head;
	while (current)
	{
		token = current->data;
		if (token->type == id_space)
		{
			current = current->next;
			token = current->data;
		}
		if (token->type == id_err_tok || !verify_token(token->type, &context))
			return (syntax_error_handler(shell, input, token));
		if (token->type == id_pipe)
			shell->pipe_count++;
		current = current->next;
	}
	return (true);
}
