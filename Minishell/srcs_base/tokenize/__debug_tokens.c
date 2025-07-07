/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __debug_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/06 10:37:48 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

void	put_char_range(char  c, int len, char *color)
{
	if (!color)
		while ( len--)
			printf("%c", c);
	else
		while (len--)
			printf("%s%c"ANS_RES, color, c);
}

void	put_debug_indicator(char *input, int start, int len)
{
	printf("%s\n", input);
	put_char_range(' ', start, NULL);
	put_char_range('^', len, ANS_R);
}

void __debug_tokens(t_list *token_list, char *input)
{
	t_item	*current;
	t_tok	*token;
	char *toktype;

	current = token_list->head;
	printf("\n =================================================\n");
	printf("\t\t[ INPUT TOKEN DEBUG ]\n\n");
	while (current)
	{
		token = current->data;
		put_debug_indicator(input, token->pos, token->size);
		if(token->type == id_pipe)
			toktype = "PIPE";
		else if(token->type == id_input)
			toktype = "REDIR_IN";
		else if(token->type == id_hdoc)
			toktype = "REDIR_HDOC";
		else if(token->type == id_output)
			toktype = "REDIR_OUT";
		else if(token->type == id_append)
			toktype = "REDIR_APPEND";
		else if(token->type == id_qdob)
			toktype = "DOUBLE_Q";
		else if(token->type == id_qsin)
			toktype = "SINGLE_Q";
		else if(token->type == id_string)
			toktype = "STRING";
		else if(token->type == id_err_tok)
			toktype = "SYNTAX_ERR";
		printf(ANS_U" -> [ %s(%d) | Index: %zu | Size: %zu ]\n\n"ANS_RES,
		 toktype, token->type, token->pos, token->size);
		current = current->next;
	}
	printf(" =================================================\n");
}
