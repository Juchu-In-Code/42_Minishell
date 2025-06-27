/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:27:28 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/24 17:04:52 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

bool	tokenize_ops(t_shell *shell, char *input, int *i)
{
	int	index;

	index = ft_strchr_index(TOKEN_OPS, input[*i]);
	if (index == -1)
		return (false);

	// set tokentype
	// save pos / pointer
	// return true

	if (index == 0)
	{
		// hacer algo
		(*i)++;
	}
	else if (index == 1)
	{
		// hacer otro algo
		(*i)++;
	}

	return (false);
}

bool	tokenize(t_shell *shell, char *input)
{
		// hacer que t_tok sea union?
		// gestionarlo con *void?
	t_tok	*token;
	int	i;
	int	c;

	i = 0;
	shell->tokens = list_create();
	if (!shell->tokens)
		return (false);
	while (input && input[i])
	{
		// create token driver
		c = input[i];
		while (ft_isspace(c))
			i++;
		tokenize_ops(shell, input, &i);
		// tokenize_strings(shell, input, &i);
		// save pos / pointersponde con ops -> if strchr ops c
		// handle operators
			// some ops behave different depending on the sorrounding context
			// det what to do w the str types
		// handle string types
		// create END token
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
