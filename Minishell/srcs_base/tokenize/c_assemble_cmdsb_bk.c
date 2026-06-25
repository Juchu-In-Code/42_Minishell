/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:04:04 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/12 21:23:11 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

static t_tok	*copy_token(t_tok *to_copy)
{
	t_tok	*token;

	token = ft_calloc(1, sizeof(t_tok));
	if (!token)
		return (NULL);
	token->type = to_copy->type;
	token->pos = to_copy->pos;
	token->size = to_copy->size;
	return (token);
}

static t_redir	*clone_rdrs(t_tok source, t_tok target)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->redir_type = source.type;
	redir->target.pos = target.pos;
	redir->target.size = target.size;
	redir->target.type = target.type;
	redir->target.state = target.state;
	return (redir);
}

static void	create_cmd_lists(t_cmd	*cmd)
{
	cmd->redirs = list_create(NULL);
	cmd->args = list_create(NULL);
	cmd->ac = 0;
}

static void	manage_redirs(t_shell *shell, int cmd, t_item *c_it, t_tok *c_t)
{
	t_item	*n_it;
	t_tok	*n_t;

	n_it = c_it->next;
	n_t = n_it->data;
	if (n_t->type == id_space)
	{
		n_it = n_it->next;
		n_t = n_it->data;
	}
	list_insert_tail(shell->cmds[cmd].redirs, clone_rdrs(*c_t, *n_t));
	c_it = n_it->next;
}

bool	assemble_cmds(t_shell *shell)
{
	t_item			*c_it;
	t_tok			*c_t;
	static int		cmd;

	shell->cmds = ft_calloc(shell->pipe_count + 1, sizeof(t_cmd));
	if (!shell->cmds)
		return (false);
	create_cmd_lists(&shell->cmds[cmd]);
	c_it = shell->tokens->head;
	while (c_it)
	{
		c_t = c_it->data;
		if (is_redir(c_t->type))
		{
			manage_redirs(shell, cmd, c_it, c_t);
			continue ;
		}
		if (is_quoted(c_t->type) || c_t->type == id_string
			|| c_t->type == id_space)
			list_insert_tail(shell->cmds[cmd].args, copy_token(c_t));
		if (c_t->type == id_pipe)
			create_cmd_lists(&shell->cmds[++cmd]);
	}
	c_it = c_it->next;
	return (true);
}
