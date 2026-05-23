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


void	execute(char *line, int ac, char **av, t_shell *shell, int *prev_read_fd, int cmd_n, int total_cmd)
{
	int fd[2];
	pipe(fd);
	pid_t pid = fork(); 

	// Both child and parent will start execution from here.
	if(pid < 0) 
	{
		ft_fprintf(2, "Error creating child");
	}
	else if(pid == 0) 
	{
		//Child
		
		//in case of no pipes + the command is builtin -> no fork;
		if(total_cmd == 1 && exec_builtin(ac, av, shell))
			return;
		
		//first command case
		if(cmd_n == 1)
			dup2(fd[1], 1);
		//last command case
		else if(cmd_n == total_cmd)
			dup2(*prev_read_fd, 0);
		//middle command case
		else
		{
			dup2(*prev_read_fd, 0);
			dup2(fd[1], 1);
		}

		//prev_read_fd and fd[1] both have to be closed because their fd's are swiched with sdin and stdout.
		//so those variables are just copies and there is no need to have them anymore.
		if(cmd_n != 1)
			close(*prev_read_fd);
		close(fd[1]);

		//i close this because the child process shares a copy with parent and it does not need a fd[0]
		//but parent needs it to pass it to the next child process
		close(fd[0]);

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
	}
}


void    loop(t_shell *shell)
{
	int	total_cmd = 4;
	int	prev_read_fd = -1; 
	int	cmd_n = 1;

	//hardcoded cmd1_ac to execute builtin
	int	cmd1_ac = 2;
	char	*line; 



	//Hardcoded Command: echo "Builtin esta ejecutandose con exito" | grep exito | sort -r | cat -e
	char **cmds_av[4];
	cmds_av[0] = (char *[]){"echo", "Builtin esta ejecutandose con exito", NULL};
	cmds_av[1] = (char *[]){"grep", "exito", NULL};
	cmds_av[2] = (char *[]){"sort", "-r", NULL};
	cmds_av[3] = (char *[]){"cat", "-e", NULL};

	while(cmd_n <= total_cmd)
	{
		//cmd_n - 1 is needed because cmds_av is looking for an INDEX in the array not the raw cmd number (starts from 1)
		line = get_line_to_exec(cmds_av[cmd_n - 1][0], shell->env);
		execute(line, cmd1_ac ,cmds_av[cmd_n - 1], shell, &prev_read_fd, cmd_n, total_cmd);
		if(line)
			free(line);
		cmd_n++;
	}

	int i = -1;
	while(++i < total_cmd)
	{
		wait(NULL);
	}
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
