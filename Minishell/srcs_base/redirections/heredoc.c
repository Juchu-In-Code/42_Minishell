/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 07:35:16 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/06 07:35:16 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

//this function generates a name for each heredoc.
//i is static to maintain the heredoc file number;
static char *get_temp_name()
{
	static int	i;
	char		*name;
	char		*num;

	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	free(num);
	return (name);
}

// this function handles the heredoc and converts it into a simple imput redirection;
// function returns a filename to store into cmd struct and mark it as INPUT redirection;
char	*process_heredoc(char *delimiter, bool has_quotes, t_shell *shell)
{
	char	*filename;
	char	*input;
	char	*to_write;
	int	fd;

	//filename is heapallocated;
	//beware memory leaks;
	filename = get_temp_name();

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
			if(input)
				free(input);
			break;
		}
		if(has_quotes == true)
			to_write = ft_strdup(input);
		else
			to_write = expand(input, shell);

		write(fd, to_write, ft_strlen(to_write));
		write(fd, "\n", 1);
		free(input);
		free(to_write);
	}
	close(fd);
	return (filename);
}
