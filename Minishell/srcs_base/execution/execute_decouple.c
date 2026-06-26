/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/25 10:02:12 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

void	cleanup_exit(t_shell *shell, int status)
{
	child_cleanup(shell);
	exit(status);
}

static	int	lonely_builtin(t_shell *shell)
{
	int bk_in;
	int bk_out;

	bk_in = dup(STDIN_FILENO);
	bk_out = dup(STDOUT_FILENO);

	if(handle_redirections(cmd->redirs) == true)
		exec_builtin(cmd->ac, cmd->final_args, shell);
	else
		shell->last_exit_code = 1;
	dup2(bk_in, STDIN_FILENO); dup2(bk_out, STDOUT_FILENO);

	close(bk_in);
	close(bk_out);
	return(-1);
}

void	parent_pipes(t_shell *shell, int *fd, int *prev_read_fd)
{
	set_signal_child();
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

	handle_pipes(shell, fd, prev_read_fd);
	if(handle_redirections(shell->cmds[i].redirs) == false)
		cleanup_exit(shell, 1);
	if((!shell->cmds[i].final_args || !shell->cmds[i].final_args[0]))
		cleanup_exit(shell, 0);
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

static pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
	int     fd[2];
	pid_t	pid;

	if(shell->pipe_count == 0 && is_builtin(cmd->final_args))
		return(lonely_builtin());
	pipe(fd);
	pid_t pid = fork();
	if(pid < 0) 
		return(error_return("Minishell: ", "Error creating child", -1));
	else if(pid == 0)
		child_process(shell, prev_read_fd, fd, i)
	parent_pipes(t_shell *shell, int *fd, int *prev_read_fd);
	return pid;
}
