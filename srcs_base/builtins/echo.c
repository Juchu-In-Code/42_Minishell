#include "../z_minishell.h"

static bool	is_dash_n(char *str, char n)
{
	int i;
	
	i = 1;		
	while (str[i])
	{
		if(str[i] != n)
			return(false);
		i++;
	}
	return(true);
}

int	echo(int argc, char **argv)
{
	bool no_new_line;
	int index;
	
	no_new_line = false;
	index = 1;
	while(index < argc && is_dash_n(argv[index], 'n') == true)
	{
		index++;
		no_new_line = true;
	}
	while(index < argc)
	{
		printf("%s", argv[index]);
		index++;
		if(index != argc)
			printf("%c", ' ');
	}
	if(no_new_line == false)
		printf("%c", '\n');
	return(0);
}

int main(int argc, char **argv)
{
	return(echo(argc, argv));
}
