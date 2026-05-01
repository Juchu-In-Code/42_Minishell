void	redirect(ssize_t fd, ssize_t redirect_to)
{
	if (fd != -1)
	{
		dup2(fd, redirect_to);
		close(fd);
	}
}

static ssize_t	open_input_file(char *filename)
{
	if ( (access(filename, F_OK) == 0) && (access(filename, R_OK) == 0) )
		return (open(filename, O_RDONLY));
	ft_fprintf(stderr, "cannot open %s", filename);
	return (-1);
}

static ssize_t	open_outfile(char *filename)
{
	ssize_t	file_output;

	file_output = open(av, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(av, F_OK | W_OK) < 0)
	{
		ft_fprintf(stderr, "cannot open %s", filename);
		return (-1);
	}
	return (file_output);
}

static ssize_t	open_outfile_append(char *filename)
{
	ssize_t	file_output;

	file_output = open(av, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (access(av, F_OK | W_OK) < 0)
	{
		ft_fprintf(stderr, "cannot open %s", filename);
		return (-1);
	}
	return (file_output);
}

static void	heredoc_manager(char *delim)
{
	char	*line;
	int		delim_len;
	ssize_t	hdoc_fd;

	delim_len = ft_strlen(delim);
	hdoc_fd = heredoc_open();
	if (hdoc_fd != -1)
	{
		while (1)
		{
			write(1, "pipe heredoc> ", 14);
			line = get_next_line(0);
			if (!line)
				return ;
			if (!ft_strncmp(line, delim, delim_len) && line[delim_len] == '\n')
			{
				free(line);
				break ;
			}
			write(hdoc_fd, line, ft_strlen(line));
			free(line);
		}
		close(hdoc_fd);
	}
}
