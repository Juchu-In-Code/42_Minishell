/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2026/04/14 12:07:26 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

t_tok	*create_token(t_tokt type, size_t i, size_t size)
{
	t_tok	*token;

	token = ft_calloc(1, sizeof(t_tok));
	if (!token)
		return (NULL);
	token->type = type;
	token->pos = i;
	token->size = size;
	return (token);
}

bool	tokenize_string(t_tok **token, char *input, int *i)
{
	int	size;

	size = 0;
	if (!input || !*input)
		return (false);
	while (input[size + *i]
		&& !ft_isspace(input[size + *i])
		&& !ft_strchr("\"\'<>|", input[size + *i]))
		size++;
	*token = create_token(id_string, *i, size);
	*i += size - 1;
	return (true);
}

bool	tokenize_qts(t_tok **token, char *input, int *i)
{
	int	match;
	int	size;

	match = ft_strchr_index(T_QTS, input[*i]);
	if (match == -1)
		return (false);
	size = ft_strchr_index(&input[*i + 1], T_QTS[match]) + 1;
	if (!size)
		*token = create_token(id_err_tok, *i, 1);
	else if (match == T_QDOB)
		*token = create_token(id_qdob, *i, size + 1);
	else if (match == T_QSIN)
		*token = create_token(id_qsin, *i, size + 1);
	*i += size;
	return (true);
}

bool	tokenize_ops(t_tok **token, char *input, int *i)
{
	int	match;

	match = ft_strchr_index(T_OPS, input[*i]);
	if (match == -1 || (match == 2 || match == 4))
		return (false);
	if (match == T_PIPE)
		*token = create_token(id_pipe, *i, 1);
	else if (match == T_IN && ft_strchr_index(T_OPS, input[*i + 1]) == T_IN)
		*token = create_token(id_hdoc, (*i)++, 2);
	else if (match == T_IN)
		*token = create_token(id_input, *i, 1);
	else if (match == T_OUT && ft_strchr_index(T_OPS, input[*i + 1]) == T_OUT)
		*token = create_token(id_append, (*i)++, 2);
	else if (match == T_OUT)
		*token = create_token(id_output, *i, 1);
	return (true);
}

bool	tokenize(t_shell *shell, char *input)
{
	t_tok	*token;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(input);
	shell->tokens = list_create(NULL);
	if (!shell->tokens)
		return (false);
	while (++i < len)
	{

		if (ft_isspace(input[i]))
		{
			list_insert_tail(shell->tokens, create_token(id_space, i, 1));
			while (ft_isspace(input[i]))
				i++;
		}
		if (!input[i])
			break;
		if (tokenize_qts(&token, input, &i)
			|| tokenize_ops(&token, input, &i)
			|| tokenize_string(&token, input, &i))
			list_insert_tail(shell->tokens, token);
		else
		 return (false);
	}
	list_insert_tail(shell->tokens, create_token(id_fin, i, 0));
	return (true);
}
