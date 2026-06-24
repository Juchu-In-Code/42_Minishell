static pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
        int     fd[2];
        //1 builtin with redirections(no child process);
        if(shell->pipe_count == 0 && is_builtin(cmd->final_args))
		single_builtin(t_cmd *cmd, t_shell *shell);

        pipe(fd);
        pid_t pid = fork();
        if(pid < 0) 
        {
                ft_fprintf(2, "Error creating child");
                return (-1);//-1 is returned because no child process is created
        }
        else if(pid == 0)
		child_process(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
        else
        {
		set_signal_parent();
                if(i != 0)
                        close(*prev_read_fd);
                *prev_read_fd = fd[PREAD];
                close(fd[PWRITE]);
                if(i == shell->pipe_count)
                        close(*prev_read_fd);
                return(pid);
        }
}
void	single_builtin(t_shell *shell, t_cmd *cmd)
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
void	child_process(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
	char    *path;

	set_signal_child();
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

	if(handle_redirections(cmd->redirs) == false)
		exit(1);
	if(!cmd->final_args || !cmd->final_args[0])
		exit(0);

	if(is_builtin(cmd->final_args))
		exit(exec_builtin(cmd->ac, cmd->final_args, shell));
	else
	{
		path = get_line_to_exec(cmd->final_args[0], shell->env);
		if(path == NULL)
		{
			ft_fprintf(2, "minishell: %s: command not found\n", cmd->final_args[0]);
			exit(127);
		}
		char **env = env_list_to_ptr(shell->env);

		execve(path, cmd->final_args, env);
		perror(cmd->final_args[0]);
		ft_free_matrix((void**)env);
		ft_free((void**)&path);
		exit(126);
	}
}
