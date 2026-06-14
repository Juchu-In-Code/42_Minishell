/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 07:35:16 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/06 07:35:16 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"

static int	open_input(char *filename)
{
	if ((access(filename, F_OK) == 0) && (access(filename, R_OK) == 0))
		return (open(filename, O_RDONLY));
	ft_fprintf(STDERR_FILENO, "cannot open %s\n", filename);
	return (-1);
}

static int	open_output(char *filename)
{
	int	file_output;

	file_output = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(filename, F_OK | W_OK) < 0)
	{
		ft_fprintf(STDERR_FILENO, "cannot open %s\n", filename);
		return (-1);
	}
	return (file_output);
}

static int	open_append(char *filename)
{
	int	file_output;

	file_output = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (access(filename, F_OK | W_OK) < 0)
	{
		ft_fprintf(STDERR_FILENO, "cannot open %s\n", filename);
		return (-1);
	}
	return (file_output);
}

//redirect returns false when some problem on opening is spot
//in happy redirection scenario -> true is returned
static	bool	redirect(t_tokt redir_type, char* file_name)
{
	ssize_t fd;

	if(redir_type == id_output)
		fd = open_output(file_name);
	else if(redir_type == id_append)
		fd = open_append(file_name);
	else //if(redir_type == id_input || redir_type == id_hdoc)
		fd = open_input(file_name);

	if(fd == -1)
		return(false);

	if(redir_type == id_output || redir_type == id_append)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);

	close(fd);
	return(true);
}

bool handle_redirections(t_list *redirs)
{
	t_item  *current_node;
	t_redir *redir_data;

	if (redirs)
		current_node = redirs->head;
	else
		current_node = NULL;

	while (current_node != NULL)
	{
		redir_data = (t_redir *)current_node->data;

		if (redirect(redir_data->redir_type, redir_data->file_name) == false)
			return(false);

		current_node = current_node->next;
	}
	return(true);
}
