#include "../z_minishell.h"

void	child_error_cleaner(t_shell *shell, char *env, char *env, int exit)
{
	perror(shell->cmds[i].final_args[0]);
	ft_free_matrix((void**)env);
	child_cleanup(shell);
	ft_free((void**)&path);
	exit(126);
}
void	cleanup_exit(t_shell *shell, int status)
{
	child_cleanup(shell);
	exit(status);
}

void	handle_pipes(t_shell *shell, int *fd, int *prev_read_fd)
{
	if(i != 0)
		dup2(*prev_read_fd, STDIN_FILENO);
	if(i != shell->pipe_count)
		dup2(fd[PWRITE], STDOUT_FILENO);
	if(i != 0)
		close(*prev_read_fd);
	close(fd[PWRITE]);
	close(fd[PREAD]);
}

void	child_process(t_shell *shell, int *prev_read_fd, int *fd, int i)
{
	char **env;
	char    *path;

	set_signal_child();
	handle_pipes(shell, fd, prev_read_fd);
	if(handle_redirections(shell->cmds[i].redirs) == false)
		child_cleanup(shell);
	if(handle_redirections(shell->cmds[i].redirs) == false)
		exit(1);
	if((!shell->cmds[i].final_args || !shell->cmds[i].final_args[0]) && child_cleanup(shell))
		exit(0);

	if(is_builtin(shell->cmds[i].final_args))
		cleanup_exit(shell, exec_builtin);
	else
	{
		path = get_line_to_exec(shell->cmds[i].final_args[0], shell->env);
		if(!path  && child_cleanup(shell))
			error_exit(shell->cmds[i].final_args[0], "command not found\n", 127);
		env = env_list_to_ptr(shell->env);
		execve(path, shell->cmds[i].final_args, env);
		child_error_cleaner(t_shell *shell, char *env, char *env, 126);
	}
}

int	lonely_builtin(t_shell *shell)
{
	int bk_in;
	int bk_out;

	bk_in = dup(STDIN_FILENO);
	bk_out = dup(STDOUT_FILENO);

	if(handle_redirections(cmd->redirs) == true)
		exec_builtin(cmd->ac, cmd->final_args, shell);
	else
		shell->last_exit_code = 1;
	dup2(bk_in, STDIN_FILENO);
	dup2(bk_out, STDOUT_FILENO);

	close(bk_in);
	close(bk_out);
	return(-1);
}

void parent_process(int *fd, int *prev_read_fd, pid)
{
	set_signal_parent();
	if(i != 0)
		close(*prev_read_fd);
	*prev_read_fd = fd[PREAD];
	close(fd[PWRITE]);
	if(i == shell->pipe_count)
	{
		close(*prev_read_fd);
		*prev_read_fd = -1;
	}
	return pid;
}

static pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
	int     fd[2];
	char    *path;

	if(shell->pipe_count == 0 && is_builtin(cmd->final_args))
		return(lonely_builtin());
	pipe(fd);
	pid_t pid = fork();
	if(pid < 0) 
		return(error_return("Minishell: ", "Error creating child", -1));
	else if(pid == 0)
		child_process(shell, prev_read_fd, fd, i)
	else
		return(parent_process(fd, prev_read_fd, pid));
}

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

static bool	alloc_args(t_cmd *cmd)
{
	int i = -1;

	cmd->final_args = ft_calloc(cmd->ac+1, sizeof(char *));
	if(!cmd->final_args)
		return false;
	i = -1;
	while (++i <= cmd->ac)
		cmd->final_args[i] = NULL;
	return true;
}

static helper_joins(t_shell, t_cmd *cmd, char *raw_input, t_tok *tok)
{
	char *part;
	char *temp;

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

static void put_args(t_cmd *cmd, char *raw_input, t_shell *shell)
{
	t_item  *curr;
	t_tok   *tok;
	int     i;

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
			helper_joins(t_shell, t_cmd *cmd, char *raw_input, t_tok *tok);
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



static void    fill_cmds_argv(t_cmd *cmd, char *raw_input, t_shell *shell)
{
	t_item  *curr;
	t_tok   *tok;
	int     i;
	char    *part;
	char    *temp;

	if(!alloc_args(cmd))
		return;
	put_args(cmd, raw_input, shell);
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
			{
				cmd->final_args[i] = part;
			}
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


int    count_cmds_args(t_list *args)
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
			//delimiter = token_to_string(&redir->target, raw_input);
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

void    execution_pipeline(t_shell *shell, char *input)
{
	int     prev_read;
	int     i;
	pid_t   last_pid;
	pid_t   pid;
	int status;

	i = -1;
	prev_read = -1;
	last_pid = -1;

	while(++i <= shell->pipe_count)
	{
		shell->cmds[i].ac = count_cmds_args(shell->cmds[i].args);
		fill_cmds_argv(&shell->cmds[i],input, shell);
	}
	i=-1;
	while(++i <= shell->pipe_count)
	{
		fill_cmds_redirs(&shell->cmds[i], input, shell);
		if(g_sigexit == 130)
		{
			heredoc_cleanup(shell);
			return;
		}
	}
	i = -1;
	while(++i <= shell->pipe_count)
	{
		//enter sin nada
		if((!shell->cmds[i].final_args || !shell->cmds[i].final_args[0]) &&(!shell->cmds[i].redirs || !shell->cmds[i].redirs->head))
		{
			if (prev_read != -1)
			{
				close(prev_read);
				prev_read = -1;
			}
			continue; 
		}

		pid = execute(&shell->cmds[i], shell, &prev_read, i);
		last_pid = pid;
	}
	if(last_pid != -1)
	{
		//explicitly waiting for the last process
		waitpid(last_pid, &status, 0);

		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if(WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
	//waiting for the rest
	i = -1;
	while(++i < shell->pipe_count)
	{
		wait(NULL);
	}
	heredoc_cleanup(shell);
}
