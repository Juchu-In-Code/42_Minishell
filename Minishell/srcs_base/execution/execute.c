/*Work in progress -> rebuild execution with clean structured args and lists
pid_t	execute(t_cmd *cmd, t_shell *shell, int *prev_pread)
{
	int pipe[2];

	//TODO: 1 builtin case with redirections;
	if(cmd->prev == NULL && cmd->next == NULL && exec_builtin(cmd->ac, cmd->av, shell))
		return(-1);//-1 PID is returned because no child process is created

	pipe(pipe);
	pid_t pid = fork(); 
	// Both child and parent will start execution from here.
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
		return (-1);//-1 is returned because no child process is created
	}
	else if(pid == 0)
	{
		//Child
		
		//first command case
		//there is a case with no pipes at all
		//it means cmd->prev == NULL but cmd->next == NULL
		//so cmd->next != NULL is needed to check if there are more pipes.
		if(cmd->prev == NULL && cmd->next != NULL)
			dup2(pipe[PWRITE], STDOUT_FILENO);
		//last command case
		else if(cmd->prev != NULL && cmd->next == NULL)
			dup2(*prev_pread, STDIN_FILENO);
		//middle command case
		else
		{
			dup2(*prev_pread, STDIN_FILENO);
			dup2(pipe[PWRITE], STDOUT_FILENO);
		}

		//prev_pread and pipe[PWRITE] both have to be closed because their fd's are swiched with sdin and stdout.
		//so those variables are just copies and there is no need to have them anymore.
		//first command does not have prev_pread -> so i avoid closing it in first command case
		if(cmd->prev != NULL)
			close(*prev_pread);
		close(pipe[PWRITE]);

		//i close this because the child process shares a copy with parent and it does not need a fd[0]
		//but parent needs it to pass it to the next child process
		close(pipe[PREAD]);

		//---------REDIRECTS are happening here ----------------------
		handle_redirections(cmd->redirs);
		//---------REDIRECTS helper func END----------------------

		//returns false if not a builtin
		//else -> executes a builtin and returns true
		if(exec_builtin(ac, av, shell))
			exit(0);
		else
		{
			execve(cmd->line, cmd->av, env_list_to_ptr(shell->env));
			perror("Command not found");
			exit(127);
		}
		return (pid);
	}
	else 
	{
		// Parent process code goes here
		// Parent has to wait for childs

		// cant close prev_pread in case of being 1st commad (no prev read)
		if(cmd->prev != NULL)
			close(*prev_pread);
		*prev_pread = pipe[PREAD];
		close(pipe[PWRITE]);
		if(cmd->next == NULL)
			close(*prev_pread);
		return(pid);
	}
}
*/

//------------THIS IS SCARY...------------------------------
//ac - is needed because some builtins need it. Only for builtins...
//line - is the full path command is executed from
//**av - all args
//shell - can be extracted from a c_loop - no need to be in cmd struct
//cmd_n and total_cmd are needed for correct pipes and process handeling (cmd_n is like a command index)
//t_list *redirs - a list of redirections one command has. 
//	cmd > redir1.txt | cmd2 > redir2.txt > append.txt | cmd 3 > redir3.txt
//	in case of executing cmd2 a t_list *redirs should contain data about redir2.txt and append.txt
//
//TODO: define what arguments should belong to cmd struct
//cmd:
//	*exec_path (*line)
//	**av
//	ac
//	redirs_list
//shell
//prev_fd
//
//total_cmd + cmd_n -> fixable with a linked list
//
//
//------------END OF SCARY DOCUMENTATION------------------------------
pid_t	execute(char *line, int ac, char **av, t_shell *shell, int *prev_read_fd, int cmd_n, int total_cmd, t_list *redirs)
{
	int fd[2];

	//in case of no pipes + the command is builtin -> no fork;
	//last exit code is handeled inside the exec function.
	//TODO:HANDLE REDIRECTIONS IN THIS CASE
	if(total_cmd == 1 && exec_builtin(ac, av, shell))
		return(-1);//-1 is returned because no child process is created


	//pipe creation and forking starts here!
	pipe(fd);
	pid_t pid = fork(); 
	// Both child and parent will start execution from here.
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
		return (-1);//-1 is returned because no child process is created
	}
	else if(pid == 0) 
	{
		//Child
		
		//will be revorked with lists	
		//first command's prev is null
		//middle command's prev and next are not nulls
		//last command's next in null
		//
		//first command case
		if(cmd_n == 1)
			dup2(fd[PWRITE], STDOUT_FILENO);
		//last command case
		else if(cmd_n == total_cmd)
			dup2(*prev_read_fd, STDIN_FILENO);
		//middle command case
		else
		{
			dup2(*prev_read_fd, STDIN_FILENO);
			dup2(fd[PWRITE], STDOUT_FILENO);
		}

		//prev_read_fd and fd[1] both have to be closed because their fd's are swiched with sdin and stdout.
		//so those variables are just copies and there is no need to have them anymore.
		if(cmd_n != 1)
			close(*prev_read_fd);
		close(fd[PWRITE]);

		//i close this because the child process shares a copy with parent and it does not need a fd[0]
		//but parent needs it to pass it to the next child process
		close(fd[PREAD]);

		//---------REDIRECTS are happening here ----------------------
		handle_redirections(redirs);
		//---------REDIRECTS helper func END----------------------

		//returns false if not a builtin
		//else -> executes a builtin and returns true
		if(exec_builtin(ac, av, shell))
			exit(0);
		else
		{
			execve(line, av, env_list_to_ptr(shell->env));
			perror("Command not found");
			exit(127);
		}
		
		return (pid);
	}
	else 
	{
		// Parent process code goes here
		// Parent has to wait for childs
		if(cmd_n != 1)
			close(*prev_read_fd);
		*prev_read_fd = fd[PREAD];
		close(fd[PWRITE]);
		if(cmd_n == total_cmd)
			close(*prev_read_fd);
		return(pid);
	}
}

