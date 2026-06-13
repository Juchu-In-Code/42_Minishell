pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i)
{
        int     fd[2];
        char    *path;
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
		//child process
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
		//wait for childs
                if(i != 0)
                        close(*prev_read_fd);
                *prev_read_fd = fd[PREAD];
                close(fd[PWRITE]);
                if(i == shell->pipe_count)
                        close(*prev_read_fd);
                return(pid);
        }
}
