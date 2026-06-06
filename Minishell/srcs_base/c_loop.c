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
//TODO: IMPLEMENT A MOCK DATA AND CHECK ALL REDIRECTIONS.
//TODO: ACCESS AFTER OPEN MAY GIVE ME A RACE CONDITION.


typedef enum e_redir_type
{
	INPUT,
	OUTPUT,
	APPEND
} t_redir_type;

typedef struct redir
{
	char*	file_name;
	t_redir_type	type;
} t_redir;

//this function generates a name for each heredoc.
//i is static to maintain the heredoc file number;
char *get_temp_name()
{
	static int	i;
	char		*name;
	char		*num;

	i = 0;
	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	free(num);
	return (name);
}


// this function handles the heredoc and converts it into a simple imput redirection;
// function returns a filename to store into cmd struct and mark it as INPUT redirection;
char	*process_heredoc(char *delimiter)
{
	char	*filename;
	char	*input;
	int	fd;

	//filename is heapallocated;
	//beware memory leaks;
	filename = get_temp_name();

	//TODO: check for incorrect permitions;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(fd < 0)
	{
		free(filename);
		return(NULL);
	}

	while(1337)
	{
		input = readline("> ");

		if(!input || ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break;
		}

		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	return (filename);
}


static int	open_input(char *filename)
{
	if ((access(filename, F_OK) == 0) && (access(filename, R_OK) == 0))
		return (open(filename, O_RDONLY));
	ft_fprintf(STDERR_FILENO, "cannot open %s", filename);
	return (-1);
}

static int	open_output(char *filename)
{
	int	file_output;

	file_output = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(filename, F_OK | W_OK) < 0)
	{
		ft_fprintf(STDERR_FILENO, "cannot open %s", filename);
		return (-1);
	}
	return (file_output);
}

static int	open_append(char *filename)
{
	int	file_output;

	file_output = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (access(filename, F_OK | W_OK) < 0)
	{
		ft_fprintf(STDERR_FILENO, "cannot open %s", filename);
		return (-1);
	}
	return (file_output);
}

//redirect returns false when some problem on opening is spot
//in happy redirection scenario -> true is returned
static	bool	redirect(t_redir_type redir_type, char* file_name)
{
	ssize_t fd;

	if(redir_type == OUTPUT)
		fd = open_output(file_name);
	else if(redir_type == APPEND)
		fd = open_append(file_name);
	else //INPUT or HEREDOC
		fd = open_input(file_name);

	if(fd == -1)
		return(false);

	if(redir_type == OUTPUT || redir_type == APPEND)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);

	close(fd);
	return(true);
}

static	t_list *create_mock_redirs()
{
	t_list *cmd_redirs = list_create();
	
	t_redir *redir2 = malloc(sizeof(t_redir));
	redir2->type = INPUT;
	redir2->file_name = "input.txt"; 

	list_insert_tail(cmd_redirs, redir2);
	

	t_redir *redir1 = malloc(sizeof(t_redir));
	redir1->type = OUTPUT;
	redir1->file_name = "output.txt"; 

	list_insert_tail(cmd_redirs, redir1);

	t_redir *redir3 = malloc(sizeof(t_redir));
	redir3->type = APPEND;
	redir3->file_name = "append.txt"; 

	list_insert_tail(cmd_redirs, redir3);
	return(cmd_redirs);
}

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
		
		
		//first command case
		if(cmd_n == 1)
			dup2(fd[1], STDOUT_FILENO);
		//last command case
		else if(cmd_n == total_cmd)
			dup2(*prev_read_fd, STDIN_FILENO);
		//middle command case
		else
		{
			dup2(*prev_read_fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
		}

		//prev_read_fd and fd[1] both have to be closed because their fd's are swiched with sdin and stdout.
		//so those variables are just copies and there is no need to have them anymore.
		if(cmd_n != 1)
			close(*prev_read_fd);
		close(fd[1]);

		//i close this because the child process shares a copy with parent and it does not need a fd[0]
		//but parent needs it to pass it to the next child process
		close(fd[0]);

		//---------REDIRECTS should be a helper func----------------------
		t_item  *current_node;
		t_redir *redir_data;

		if (redirs)
			current_node = redirs->head;
		else
			current_node = NULL;

		while (current_node != NULL)
		{
			redir_data = (t_redir *)current_node->data;

			if (redirect(redir_data->type, redir_data->file_name) == false)
				exit(1); 

			current_node = current_node->next;
		}
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
		*prev_read_fd = fd[0];
		close(fd[1]);
		if(cmd_n == total_cmd)
			close(*prev_read_fd);
		return(pid);
	}
}


void    loop(t_shell *shell)
{
	int	total_cmd = 4;
	int	prev_read_fd = -1; 
	int	cmd_n = 1;
	pid_t	pid;
	pid_t	last_pid;

	//hardcoded cmd1_ac to execute builtin
	int	cmd1_ac = 2;
	char	*line; 


	t_list *redirs = create_mock_redirs();
	//Hardcoded Command: echo "Testing minishell" | cat -e | ls /not_found | grep minishell
	char **cmds_av[4];

	cmds_av[0] = (char *[]){"wc", "-l", NULL};
	cmds_av[1] = (char *[]){"cat", "-e", NULL};
	cmds_av[2] = (char *[]){"ls", "/not_found", NULL};
	cmds_av[3] = (char *[]){"grep", "minishell", NULL};

	while(cmd_n <= total_cmd)
	{
		//cmd_n - 1 is needed because cmds_av is looking for an INDEX in the array not the raw cmd number (starts from 1)
		line = get_line_to_exec(cmds_av[cmd_n - 1][0], shell->env);
		pid = execute(line, cmd1_ac ,cmds_av[cmd_n - 1], shell, &prev_read_fd, cmd_n, total_cmd, redirs);
		if(line)
			free(line);
		if(cmd_n == total_cmd)
			last_pid = pid;
		cmd_n++;
	}

	int status;
	waitpid(last_pid, &status, 0);

	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	
	int i = -1;
	//total_cmd - 1 is because the last child is finished with waitpid, so wait has to wait for total_cmd - 1 childs
	while(++i < total_cmd - 1)
	{
		wait(NULL);
	}
	printf("Command executed: echo Testing minishell \n");
	printf("\nLast exit code: %d\n", shell->last_exit_code);
}	
	
	
	/*
	char	*input;
	char	*line;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{

		char **av = ft_split(input, ' ');
		int ac = ft_get_array_length(av);

		if(ac)
		{
			//it's a boolean function (true on detected builtin)	
			if(!exec_builtin(ac, av, shell))
			{
				//line is heap allocated
				line = get_line_to_exec(av[0], shell->env);
				if(line)
				{
					
					printf("line: %s\n", line);
					execute(line, av, shell->env);
					free(line);
					shell->last_exit_code = 0;
				}
				else
				{
					ft_fprintf(2, "minishell: %s: No such file or directory\n", av[0]);
					shell->last_exit_code = 127;
				}
			}
		}
		ft_free_matrix((void *)av);
		free(input);
		input = NULL;
	}

}
	*/
