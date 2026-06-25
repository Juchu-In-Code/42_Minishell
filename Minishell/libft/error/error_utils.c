/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:34:39 by jgalizio          #+#    #+#             */
/*   Updated: 2026/06/25 10:24:07 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	error_call(char *err, char *msg)
{
	static int	err_count;

	if (!err)
	{
		if (!msg)
			ft_fprintf(2, "[!]\t Error call, ocurrences: %i\n", ++err_count);
		else
			ft_fprintf(2, "[!]\t Error: %s\n", msg);
	}
	else
	{
		if (!*err)
			err = "<Empty field>";
		if (!msg)
			ft_fprintf(2, "[!]\t Error call, ocurrences: %i\n", ++err_count);
		else
			ft_fprintf(2, "[!]\t%s: %s\n", err, msg);
	}
}

int	error_return(char *err, char *msg, int return_code)
{
	error_call(err, msg);
	return (return_code);
}

void	error_exit(char *err, char *msg, int exit_code)
{
	error_call(err, msg);
	exit(exit_code);
}

void	perror_call(char *err, char *msg)
{
	if (!err)
	{
		if (!msg)
			perror("[!]\t Error: ");
		else
			ft_fprintf(2, "[!]\t Error: %s\n", msg);
	}
	else
	{
		if (!*err)
			err = "<Empty field>";
		if (!msg)
			perror(err);
		else
			ft_fprintf(2, "[!]\t%s: %s\n", err, msg);
	}
}

void	perror_exit(char *err, char *msg, int exit_code)
{
	perror_call(err, msg);
	exit(exit_code);
}
