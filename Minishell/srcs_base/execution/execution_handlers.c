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

static void	handle_argv(t_shell *shell, char *input)
{
	int	i;

	i = -1;
	while (++i <= shell->pipe_count)
	{
		shell->cmds[i].ac = count_cmds_args(shell->cmds[i].args);
		fill_cmds_argv(&shell->cmds[i], input, shell);
	}
}

static	bool	handle_redirs(t_shell *shell, char *input)
{
	int	i;

	i = -1;
	while (++i <= shell->pipe_count)
	{
		fill_cmds_redirs(&shell->cmds[i], input, shell);
		if (g_sigexit == 130)
		{
			heredoc_cleanup(shell);
			return (false);
		}
	}
	return (true);
}

static pid_t	handle_execution(t_shell *shell)
{
	pid_t	last_pid;
	int		prev_read;
	int		i;

	i = -1;
	prev_read = -1;
	while (++i <= shell->pipe_count)
	{
		if ((!shell->cmds[i].final_args || !shell->cmds[i].final_args[0])
			&& (!shell->cmds[i].redirs || !shell->cmds[i].redirs->head))
		{
			if (prev_read != -1)
			{
				close(prev_read);
				prev_read = -1;
			}
			continue ;
		}
		last_pid = execute(&shell->cmds[i], shell, &prev_read, i);
	}
	return (last_pid);
}

static void	handle_exit_status(t_shell *shell, pid_t last_pid)
{
	int	status;
	int	i;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
	i = -1;
	while (++i < shell->pipe_count)
		wait(NULL);
}

void	execution_pipeline(t_shell *shell, char *input)
{
	pid_t	last_pid;

	last_pid = -1;
	handle_argv(shell, input);
	if (!handle_redirs(shell, input))
		return ;
	last_pid = handle_execution(shell);
	handle_exit_status(shell, last_pid);
	heredoc_cleanup(shell);
}
