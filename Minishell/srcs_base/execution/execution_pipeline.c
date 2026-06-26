/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/26 11:34:22 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

static char	*join_args(t_shell *shell, char *in, char *arg, t_tok *tok)
{
	char	*to_return;
	char	*part;
	char	*temp;

	part = expand_token(tok, in, shell);
	if (!part)
		part = ft_strdup("");
	if (!arg)
		return (part);
	temp = arg;
	to_return = ft_strjoin(temp, part);
	ft_free((void **)&temp);
	ft_free((void **)&part);
	return (to_return);
}

void	fill_cmds_argv(t_cmd *cmd, char *in, t_shell *shell)
{
	t_item	*curr;
	t_tok	*tok;
	int		i;

	i = 0;
	cmd->final_args = ft_calloc(cmd->ac + 1, sizeof (char *));
	if (!cmd->final_args)
		return ;
	curr = cmd->args->head;
	while (curr)
	{
		tok = (t_tok *)curr->data;
		if (tok->type == id_space)
		{
			if (cmd->final_args[i] != NULL)
				i++;
		}
		else
			cmd->final_args[i] = join_args(shell, in, cmd->final_args[i], tok);
		curr = curr->next;
	}
}

static void	heredoc_setup(t_shell *shell, t_redir *redir, char *in)
{
	char	*del;
	bool	has_quotes;

	has_quotes = false;
	if (redir->target.type == id_qsin || redir->target.type == id_qdob)
	{
		has_quotes = true;
		del = ft_substr(in, redir->target.pos + 1, redir->target.size - 2);
	}
	else
		del = token_to_string(&redir->target, in);
	printf("Delimiter -> %s\n", del);
	set_signal_heredoc();
	redir->file_name = process_heredoc(del, has_quotes, shell);
	ft_free((void **)&del);
}

void	fill_cmds_redirs(t_cmd *cmd, char *in, t_shell *shell)
{
	t_item		*curr;
	t_redir		*redir;
	int			fd_tty;

	fd_tty = dup(STDIN_FILENO);
	curr = cmd->redirs->head;
	while (curr)
	{
		redir = (t_redir *)curr->data;
		if (redir->redir_type == id_hdoc)
		{
			heredoc_setup(shell, redir, in);
			if (g_sigexit == 130)
			{
				dup2(fd_tty, STDIN_FILENO);
				close(fd_tty);
				return ;
			}
		}
		else
			redir->file_name = expand_token(&redir->target, in, shell);
		curr = curr->next;
	}
	close(fd_tty);
}
