/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:06 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 18:21:20 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

static void	free_redir(void *redir_passed)
{
	t_redir	*redir_to_free;

	redir_to_free = (t_redir *)redir_passed;
	if (!redir_to_free)
		return ;
	if (redir_to_free->file_name)
	{
		ft_free((void **)&redir_to_free->file_name);
		redir_to_free->file_name = NULL;
	}
	ft_free((void **)&redir_to_free);
	redir_to_free = NULL;
}

void	free_cmds(t_shell *shell)
{
	int	i;

	i = -1;
	if (!shell->cmds)
		return ;
	while (++i <= shell->pipe_count)
	{
		list_free(&shell->cmds[i].redirs, free_redir);
		list_free(&shell->cmds[i].args, NULL);
		ft_free_matrix((void **)shell->cmds[i].final_args);
		ft_free((void *)&shell->cmds[i]);
	}
	ft_free((void **)&shell->cmds);
	shell->cmds = NULL;
}
