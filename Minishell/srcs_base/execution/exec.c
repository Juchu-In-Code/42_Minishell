void try_to_exec(char *line, char **args, char **env)
{
	pid = fork(); 
	// Both child and parent will now start execution from here.
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
	}
	else if(pid == 0) 
	{
		// This is the child process
		execve(line, args, env);
	}
	else 
	{
		// Parent process code goes here
		// Parent has to wait for childs
		wait(NULL);
	}
}
