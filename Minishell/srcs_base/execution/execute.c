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
        /*TODO:handle 1 builtin with redirections(no child process);
        if(shell->pipe_count == 0 && exec_builtin(cmd->ac, cmd->final_args, shell))
                return(-1);*/

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
                //TODO:handle redirections until executing
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

static void    fill_cmds_argv(t_cmd *cmd, char *raw_input)
{
        t_item  *curr;
        t_tok   *tok;
        int     i;

        cmd->final_args = malloc(sizeof(char *) * (cmd->ac + 1));
        if(!cmd->final_args)
                return;
        curr = cmd->args->head;
        i = 0;
        while(curr != NULL)
        {
                tok = (t_tok*)curr->data;
                cmd->final_args[i] = token_to_string(tok, raw_input);
                curr = curr->next;
                i++;
        }
        cmd->final_args[i] = NULL;
}

static void    fill_cmds_redirs(t_cmd *cmd, char *raw_input)
{
        t_item  *curr;
        t_redir   *redir;
	char	*delimiter;

        curr = cmd->redirs->head;
        while(curr != NULL)
        {
                redir = (t_redir*)curr->data;
		if(redir->redir_type == id_hdoc)
		{
			delimiter = token_to_string(&redir->target, raw_input);
				
			printf("DEBUG: delimiter -> %s\n", delimiter);
			redir->file_name = process_heredoc(delimiter);
			free(delimiter);
		}
		else
			redir->file_name = token_to_string(&redir->target, raw_input);
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
        while(++i <= shell->pipe_count)
        {
		fill_cmds_argv(&shell->cmds[i], input);
                fill_cmds_redirs(&shell->cmds[i], input);
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
