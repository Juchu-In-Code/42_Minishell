/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:57 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"
//TODO:refactor execution + redirections integration;

pid_t	execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
	int	fd[2];
	char	*path;
	//TODO:handle 1 builtin with redirections(no child process);
	if(shell->pipe_count == 0 && exec_builtin(cmd->ac, cmd->final_args, shell))
		return(-1);
	
	pipe(fd);
	pid_t pid = fork();
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
		return (-1);//-1 is returned because no child process is created
	}
	else if(pid == 0)
	{
		if(shell->pipe_count == 0)
		{

		}
		else if(i == 0)
		{
			dup2(fd[PWRITE], STDOUT_FILENO);
		}
		else if(i == shell->pipe_count)
		{
			dup2(*prev_read_fd, STDIN_FILENO);
		}
		else
		{
			dup2(*prev_read_fd, STDIN_FILENO);
			dup2(fd[PWRITE], STDOUT_FILENO);
		}
		if(i != 0)
			close(*prev_read_fd);
		close(fd[PWRITE]);
		close(fd[PREAD]);
		//TODO:handle redirections until executing
		
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
		return (pid);
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

char	*token_to_string(t_tok *token, char *raw_line)
{
        char    *token_str;
        token_str = ft_substr(raw_line, token->pos, token->size);
        return(token_str);
}

void	materialize_cmd(t_cmd *cmd, char *raw_input)
{
	t_item	*curr;
	t_tok	*tok;
	int	i;

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

void	execution_pipeline(t_shell *shell, char *input)
{
	int	prev_read;
	int	i;
	pid_t	last_pid;
	pid_t	pid;

	i = -1;
	prev_read = -1;
	last_pid = -1;
	while(++i <= shell->pipe_count)
	{
		materialize_cmd(&shell->cmds[i], input);
		pid = execute(&shell->cmds[i], shell, &prev_read, i);
		last_pid = pid;
	}
	int status;
	waitpid(last_pid, &status, 0);

	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	i = -1;
	while(++i < shell->pipe_count)
	{
		wait(NULL);
	}
}

void	loop(t_shell *shell)
{
	char	*input;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{

		tokenize(shell, input);
		if (*input)
			debug_tokens(shell->tokens, input);
		shell->pipe_count = token_syntax_checker(shell->tokens, input);
		assemble_cmds(shell);
		if(shell->cmds)
			execution_pipeline(shell, input);
		free(input);
		input = NULL;
	}
}
