#include "z_minishell.h"
/*Builtins: 
every builtin int this project has a specific signature
to be considered a builtin function.
Signature: "int func(int ac, char **av, t_shell shell)"

So every builtin function can enter the t_builtin struct 
that consists of a function pointer and a name
and can be called by exec_builtuin function afterwards.

Return value is of type int -> builtin function will
return it's exit code as a regular integer so 
exec_builtin() can set shell->last_exit_code to 
that returned integer value;

Every builtin will get the whole line as av
example:
>>export LEET=1337 
av[0] = "export"
av[1] = "LEET=1337"
so it should operate from av[1] NOT av[0];*/

static const t_builtin *builtin_setup()
{
    static t_builtin builtins[] = {
		{"echo", ft_echo},
		{"cd", ft_cd},
		{"pwd", ft_pwd},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit},
		{NULL, NULL}
    };
    
    return builtins;
}

bool exec_builtin(int ac, char **av, t_shell *shell)
{
	const t_builtin *builtins = builtin_setup();
	int i = 0;

	if (!av || !av[0] || !av[0][0])
		return false; 

	while(builtins[i].name != NULL)
	{
		if(ft_strcmp(av[0], builtins[i].name) == 0)
		{
			int result = builtins[i].func(ac, av, shell);
			shell->last_exit_code = (unsigned char)result;
			return true;
		}
		i++;
	}
	return false;
}

bool is_builtin(char **av)
{
	const t_builtin *builtins = builtin_setup();
	int i = 0;

	if (!av || !av[0] || !av[0][0])
		return false; 

	while(builtins[i].name != NULL)
	{
		if(ft_strcmp(av[0], builtins[i].name) == 0)
			return true;
		i++;
	}
	return false;
}
