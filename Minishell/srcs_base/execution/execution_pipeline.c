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
char *expand_token(t_tok *tok, char *raw_input, t_shell *shell)
{
	char *str;
	char *expanded;

	if (tok->type == id_qsin || tok->type == id_qdob)
		str = ft_substr(raw_input, tok->pos + 1, tok->size - 2);
	else
		str = ft_substr(raw_input, tok->pos, tok->size);

	if(tok->type == id_qsin)
		return (str);

	expanded = expand(str, shell);
	ft_free((void**)&str);
	return (expanded);
}

static void    fill_cmds_argv(t_cmd *cmd, char *raw_input, t_shell *shell)
{
	t_item  *curr;
	t_tok   *tok;
	int     i;
	char    *part;
	char    *temp;

	cmd->final_args = ft_calloc(cmd->ac+1, sizeof(char *));
	if(!cmd->final_args)
		return;
	i = -1;
	while (++i <= cmd->ac)
		cmd->final_args[i] = NULL;
	curr = cmd->args->head;
	i = 0;
	while(curr != NULL)
	{
		tok = (t_tok*)curr->data;
		if (tok->type == id_space)
		{
			if (cmd->final_args[i] != NULL)
				i++;
		}
		else
		{
			part = expand_token(tok, raw_input, shell);
			if (!part)
				part = ft_strdup("");
			if (cmd->final_args[i] == NULL)
				cmd->final_args[i] = part;
			else
			{
				temp = cmd->final_args[i];
				cmd->final_args[i] = ft_strjoin(temp, part);
				ft_free((void**)&temp);
				ft_free((void**)&part);
			}
		}
		curr = curr->next;
	}
	if (cmd->final_args[i] != NULL)
		i++;
	cmd->final_args[i] = NULL;
}


static	int    count_cmds_args(t_list *args)
{
	t_item	*curr;
	t_tok	*tok;
	int     count;
	bool    has_content; 

	if (!args || !args->head)
		return (0);
	count = 0;
	has_content = false;
	curr = args->head;
	while (curr != NULL)
	{
		tok = (t_tok *)curr->data;
		if (tok->type == id_space)
		{
			if (has_content == true)
			{
				count++;
				has_content = false; 
			}
		}
		else
			has_content = true;
		curr = curr->next;
	}
	if (has_content == true)
		count++;
	return (count);
}

static void    fill_cmds_redirs(t_cmd *cmd, char *raw_input, t_shell *shell)
{
	t_item  *curr;
	t_redir   *redir;
	char	*delimiter;
	bool	has_quotes;
	int	fd_tty;

	fd_tty = dup(STDIN_FILENO);
	curr = cmd->redirs->head;
	while(curr != NULL)
	{
		redir = (t_redir*)curr->data;
		if(redir->redir_type == id_hdoc)
		{
			if (redir->target.type == id_qsin || redir->target.type == id_qdob)
			{
				has_quotes = true;
				delimiter = ft_substr(raw_input, redir->target.pos+1, redir->target.size-2);
			}
			else
			{
				has_quotes = false;
				delimiter = token_to_string(&redir->target, raw_input);
			}

			printf("Delimiter -> %s\n", delimiter);
			set_signal_heredoc();
			redir->file_name = process_heredoc(delimiter, has_quotes, shell);
			ft_free((void**)&delimiter);

			if(g_sigexit == 130)
			{
				dup2(fd_tty, STDIN_FILENO);
				close(fd_tty);
				return;
			}
		}
		else
			redir->file_name = expand_token(&redir->target, raw_input, shell);

		curr = curr->next;
	}
	close(fd_tty);
}

static	void handle_argv(t_shell *shell, char *input)
{
	int i;
	
	i = -1;
	while(++i <= shell->pipe_count)
	{
		shell->cmds[i].ac = count_cmds_args(shell->cmds[i].args);
		fill_cmds_argv(&shell->cmds[i],input, shell);
	}
}

static	bool	handle_redirs(t_shell *shell, char *input)
{
	int i;

	i=-1;
	while(++i <= shell->pipe_count)
	{
		fill_cmds_redirs(&shell->cmds[i], input, shell);
		if(g_sigexit == 130)
		{
			heredoc_cleanup(shell);
			return false;
		}
	}
	return true;
}

static pid_t	handle_execution(t_shell *shell)
{
	pid_t last_pid;
	int prev_read;
	int	i;
	i = -1;
	prev_read = -1;

	while(++i <= shell->pipe_count)
	{
		if((!shell->cmds[i].final_args || !shell->cmds[i].final_args[0]) && (!shell->cmds[i].redirs || !shell->cmds[i].redirs->head))
		{
			if (prev_read != -1)
			{
				close(prev_read);
				prev_read = -1;
			}
			continue; 
		}
		last_pid = execute(&shell->cmds[i], shell, &prev_read, i);
	}
	return	last_pid;
}

static	void handle_exit_status(t_shell *shell, pid_t last_pid)
{
	int status;
	int i;

	if(last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if(WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
	i = -1;
	while(++i < shell->pipe_count)
		wait(NULL);
}

void    execution_pipeline(t_shell *shell, char *input)
{
	pid_t   last_pid;
	last_pid = -1;

	handle_argv(shell, input);
	if(!handle_redirs(shell, input))
		return;
	last_pid = handle_execution(shell);
	handle_exit_status(shell, last_pid);
	heredoc_cleanup(shell);
}
