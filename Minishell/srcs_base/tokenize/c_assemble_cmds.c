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

static t_item	*manage_redirs(t_shell *shell, t_item *c_item, int cmd)
{
	t_item	*n_item;
	t_tok	*n_token;
	t_tok	*c_token;

	c_token = c_item->data;
	n_item = c_item->next;
	n_token = n_item->data;
	if (n_token->type == id_space)
	{
		n_item = n_item->next;
		n_token = n_item->data;
	}
	list_insert_tail(shell->cmds[cmd].redirs, clone_rdrs(*c_token, *n_token));
	return (n_item->next);
}

bool	assemble_cmds(t_shell *shell)
{
	t_item		*c_item;
	t_tok		*c_token;
	int			cmd;

	cmd = 0;
	shell->cmds = ft_calloc(shell->pipe_count + 1, sizeof(t_cmd));
	create_cmd_lists(&shell->cmds[cmd]);
	c_item = shell->tokens->head;
	while (c_item)
	{
		c_token = c_item->data;
		if (is_redir(c_token->type))
		{
			c_item = manage_redirs(shell, c_item, cmd);
			continue ;
		}
		if (is_quoted(c_token->type) || c_token->type == id_string
			|| c_token->type == id_space)
			list_insert_tail(shell->cmds[cmd].args, copy_token(c_token));
		if (c_token->type == id_pipe && ++cmd)
			create_cmd_lists(&shell->cmds[cmd]);
		c_item = c_item->next;
	}
	return (true);
}
