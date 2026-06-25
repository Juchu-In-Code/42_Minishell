/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 07:35:16 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/25 13:48:07 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

// this function generates a name for each heredoc.
// i is static to maintain the heredoc file number;
static char	*get_temp_name(void)
{
	static int	i;
	char		*name;
	char		*num;

	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	ft_free((void **)&num);
	return (name);
}

static void	write_heredoc(int fd, char *delimiter, bool quotes, t_shell *shell)
{
	char	*input;
	char	*to_write;

	while (1337)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, delimiter) == 0)
		{
			if (input)
				ft_free((void **)&input);
			break ;
		}
		if (quotes == true)
			to_write = ft_strdup(input);
		else
			to_write = expand(input, shell);
		write(fd, to_write, ft_strlen(to_write));
		write(fd, "\n", 1);
		ft_free((void **)&input);
		ft_free((void **)&to_write);
	}
}

char	*process_heredoc(char *delimiter, bool has_quotes, t_shell *shell)
{
	char	*filename;
	int		fd;

	filename = get_temp_name();
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_free((void **)&filename);
		return (NULL);
	}
	write_heredoc(fd, delimiter, has_quotes, shell);
	close(fd);
	return (filename);
}
