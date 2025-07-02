/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 19:46:22 by jgalizio         ###   ########.fr       */
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

bool	tokenize_qts(t_tok *token, char *input, int *i)
{
	int	match;
	int	match_end;

	match = ft_strchr_index(T_QTS, input[*i]);
	match_end = ft_strchr_index(&input[*i + 1], T_QTS[match]);
	if (match == -1)
		return (false);
	if (match_end == -1)
		token = create_token(err_tok, *i, 0);
	else if (match == T_QDOB)
		token = create_token(q_dob, *i, match_end);
	else if (match == T_QSIN)
		token = create_token(q_sin, *i, match_end);
	*i += match_end;
	return (true);
}

bool	tokenize_ops(t_tok *token, char *input, int *i)
{
	int	match;

	match = ft_strchr_index(T_OPS, input[*i]);
	if (match == -1)
		return (false);
	if (match == pipex)
		token = create_token(pipex, *i, 1);
	else if (match == T_IN && ft_strchr_index(T_OPS, input[*i + 2]) == T_IN)
	{
		token = create_token(r_hdoc, *i, 2);
		(*i)++;
	}
	else if (match == T_IN)
		token = create_token(r_input, *i, 1);
	else if (match == T_OUT && ft_strchr_index(T_OPS, input[*i + 1]) == T_OUT)
	{
		token = create_token(r_append, *i, 2);
		(*i)++;
	}
	else if (match == T_OUT)
		token = create_token(r_output, *i, 1);
	return (true);
}

bool	tokenize(t_shell *shell, char *input)
{
	t_tok	*token;
	int		i;
	int		c;

	i = 0;
	shell->tokens = list_create();
	if (!shell->tokens)
		return (false);
	while (input && input[i])
	{
		c = input[i];
		while (ft_isspace(c))
			i++;
		tokenize_qts(token, input, &i);
		tokenize_ops(token, input, &i);
		// tokenize_string(token, input, &i);
		list_insert_tail(shell->env, token);
		// check fin string
		i++;
	}
	return (true);
}

// func tokenize
//
// while input
//	skip whitespace
//	hacer comprobaciones
//	por cada token que se encuentre, avanzar hasta terminar de consumirlo.
//	en caso de encontrar un token que no cierre, guardar el token abierto y registrar el nuevo
//	si un token no se puede terminar de consumir, quiere decir que hay o un error de sintaxis
//	en caso de encontrar un token incorrecto, (como un token de cierre sin uno de apertura antes) error de sintaxis
//
