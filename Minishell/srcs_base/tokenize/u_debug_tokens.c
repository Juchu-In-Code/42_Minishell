/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_debug_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/12 20:18:05 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

static void	print_toktype(t_tokt toktype)
{
	const char	*toks[] = {
		"PIPE", "REDIR_IN", "REDIR_HDOC",
		"REDIR_OUT", "REDIR_APPEND", "DOUBLE_Q",
		"SINGLE_Q", "STRING", "PAREN_L", "PAREN_R",
		"SYNTAX_ERR", "SPACE", "FIN" };

	printf(ANS_Y" %s", toks[toktype]);
}

void	debug_tokens(t_list *token_list, char *input)
{
	t_item	*current;
	t_tok	*token;

	current = token_list->head;
	printf("\n =================================================\n");
	printf("\t\t[ INPUT TOKEN DEBUG ]\n\n");
	while (current)
	{
		token = current->data;
		if (token->type == id_fin)
			break ;
		put_debug_indicator(input, token->pos, token->size);
		print_toktype(token->type);
		printf(ANS_U" -> [ ");
		printf("Index: %zu | Size: %zu ]\n\n"ANS_RES, token->pos, token->size);
		current = current->next;
	}
	printf(" =================================================\n");
}
