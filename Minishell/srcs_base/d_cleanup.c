/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:06 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/12 18:21:20 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"
//to use with "void	list_free(t_list *list, t_free free_func)" as a t_free function.
void free_env_entry(void *env_entry)
{
    t_env *entry = (t_env*)env_entry;
    if(!entry)
        return;
    if(entry->dict[KEY])
    {    
        free(entry->dict[KEY]);
        entry->dict[KEY] = NULL;
    }
    if(entry->dict[VAL])
    {   
        free(entry->dict[VAL]);
        entry->dict[VAL] = NULL;
    }
    free(entry);
}

void heredoc_cleanup(t_shell *shell)
{

	int	i;
	t_item	*curr;
	t_redir	*redir;

	i = -1;
	while (++i <= shell->pipe_count)
	{
		if(!shell->cmds || !shell->cmds[i].redirs ||!shell->cmds[i].redirs->head)
			continue;

		curr = shell->cmds[i].redirs->head;
		while(curr != NULL)
		{
			redir = (t_redir *)curr->data;
			if(redir->redir_type == id_hdoc && redir->file_name != NULL)
				unlink(redir->file_name);
			curr = curr->next;
		}
	}
}

//for now only list_free() inside, but i expect more cleaning to be done in the future.
void cleanup(t_shell *shell)
{
   list_free(shell->env, free_env_entry);
   return;
}
