/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/26 14:13:33 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"


static pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
        int     fd[2];
        char    *path;
        //1 builtin with redirections(no child process);
        if(shell->pipe_count == 0 && is_builtin(cmd->final_args))
	{
		int bk_in;
		int bk_out;

		bk_in = dup(STDIN_FILENO);
		bk_out = dup(STDOUT_FILENO);

		if(handle_redirections(cmd->redirs) == true)
			exec_builtin(cmd->ac, cmd->final_args, shell);
		dup2(bk_in, STDIN_FILENO);
		dup2(bk_out, STDOUT_FILENO);

		close(bk_in);
		close(bk_out);
		return(-1);
	}

        pipe(fd);
        pid_t pid = fork();
        if(pid < 0) 
        {
                ft_fprintf(2, "Error creating child");
                return (-1);//-1 is returned because no child process is created
        }
        else if(pid == 0)
        {
                //every command have to redirect input except the first one
                if(i != 0)
                        dup2(*prev_read_fd, STDIN_FILENO);
                //every command have to redirect output except the last one
                if(i != shell->pipe_count)
                        dup2(fd[PWRITE], STDOUT_FILENO);

                if(i != 0)
                        close(*prev_read_fd);

                close(fd[PWRITE]);
                close(fd[PREAD]);
                //handle redirections until executing
		if(handle_redirections(cmd->redirs) == false)
			exit(1);

                if(exec_builtin(cmd->ac, cmd->final_args, shell))
                        exit(0);
                else
                {
                        path = get_line_to_exec(cmd->final_args[0], shell->env);
                        if(path == NULL)
                        {
                                ft_fprintf(2, "minishell: %s: command not found\n", cmd->final_args[0]);
                                exit(127);
                        }

                        execve(path, cmd->final_args, env_list_to_ptr(shell->env));
                        perror(cmd->final_args[0]);
                        free(path);
                        exit(126);
                }
        }
        else
        {
                if(i != 0)
                        close(*prev_read_fd);
                *prev_read_fd = fd[PREAD];
                close(fd[PWRITE]);
                if(i == shell->pipe_count)
                        close(*prev_read_fd);
                return(pid);
        }
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
    free(str); 
    return (expanded);
}

static void    fill_cmds_argv(t_cmd *cmd, char *raw_input, t_shell *shell)
{
	t_item  *curr;
	t_tok   *tok;
	int     i;
	char    *part;
	char    *temp;

	cmd->final_args = malloc(sizeof(char *) * (cmd->ac + 1));
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

		//Space case:
		if (tok->type == id_space)
		{
			if (cmd->final_args[i] != NULL)
			i++;
		}
		//Normal string
		else
		{
			//TODO: expand here
			//part = token_to_string(tok, raw_input);
			//shell is needed to access env variables
			part = expand_token(tok, raw_input, shell);

			// if part is NULL - in case of empty expanded var -> set it to "" 
			if (!part)
				part = ft_strdup("");

			// first part
			if (cmd->final_args[i] == NULL)
			{
				cmd->final_args[i] = part;
			}
			// other parts to join
			else
			{
				temp = cmd->final_args[i];
				cmd->final_args[i] = ft_strjoin(temp, part);

				free(temp);
				free(part);
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

        curr = cmd->redirs->head;
        while(curr != NULL)
        {
                redir = (t_redir*)curr->data;
		if(redir->redir_type == id_hdoc)
		{
			delimiter = token_to_string(&redir->target, raw_input);
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
				
			printf("DEBUG: delimiter -> %s\n", delimiter);
			redir->file_name = process_heredoc(delimiter, has_quotes, shell);
			free(delimiter);
		}
		else
		{
				redir->file_name = expand_token(&redir->target, raw_input, shell);
		}
                curr = curr->next;
        }
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
	printf("DEBUG: Pipe count is %d\n", shell->pipe_count);
        while(++i <= shell->pipe_count)
        {
		shell->cmds[i].ac = count_cmds_args(shell->cmds[i].args);
                fill_cmds_argv(&shell->cmds[i],input, shell);
		fill_cmds_redirs(&shell->cmds[i], input, shell);

		if(!shell->cmds[i].final_args || !shell->cmds[i].final_args[0])
			continue;

                pid = execute(&shell->cmds[i], shell, &prev_read, i);
                last_pid = pid;
        }
	if(last_pid != -1)
	{
		//explicitly waiting for the last process
		waitpid(last_pid, &status, 0);

		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		//waiting for the rest
		i = -1;
		while(++i < shell->pipe_count)
		{
			wait(NULL);
		}
	}
}
