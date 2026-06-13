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
