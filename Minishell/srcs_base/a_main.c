/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:07:41 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 18:12:01 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

// de momento esta func existe solo para que cc no se queje por ac y av
void	verify(int ac, char **av)
{
	(void)ac;
	(void)av;
	// TODO:
	//	separar en otro archivo
	//	verificar cantidad de imputs
	//		a) quejarse y salir si hay algo
	//		b) permitir flags y quejarse si no son las correctas
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	verify(ac, av);
	setup(&shell, env);
	loop(&shell);
	// cleanup
	return (0);
}
