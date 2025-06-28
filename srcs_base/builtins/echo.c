#include "../z_minishell.h"

static int	isOption(char *str, char option)
{
	int i;
	
	i = 1;		//i == 1 -> to skip '-';
	while (str[i])
	{
		if(str[i] != option)
			return(1);
		i++;
	}
	return(0);
}

int	main(int argc, char **argv)
{
	int isN;
	int index;
	
	isN = 0;
	index = 1;
	if(argc > 1)
	{
		while(index < argc && isOption(argv[index], 'n') == 0)
		{
			index++;
			isN = 1;
		}
		while(index < argc)
		{
			ft_putstr_fd(argv[index],1);
			index++;
			if(index != argc)
			ft_putchar_fd(' ', 1);
		}
	}
		if(isN == 0)
			ft_putchar_fd('\n', 1);
	return(0);
}
