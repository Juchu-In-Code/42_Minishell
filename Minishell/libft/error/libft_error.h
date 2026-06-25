/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:53:16 by jgalizio          #+#    #+#             */
/*   Updated: 2026/06/25 10:34:19 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ERROR_H
# define LIBFT_ERROR_H

# include "../libft_incs.h"

void	error_call(char *err, char *msg);
void	error_exit(char *err, char *msg, int exit_code);
void	perror_call(char *err, char *msg);
void	perror_exit(char *err, char *msg, int exit_code);
int		error_return(char *err, char *msg, int return_code);

#endif
