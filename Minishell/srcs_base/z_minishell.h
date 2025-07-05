/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:11:35 by jgalizio          #+#    #+#             */
/*   Updated: 2025/07/02 19:46:05 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Z_MINISHELL_H
# define Z_MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*  __  __                           */
/* |  \/  | __ _  ___ _ __ ___  ___  */
/* | |\/| |/ _` |/ __| '__/ _ \/ __| */
/* | |  | | (_| | (__| | | (_) \__ \ */
/* |_|  |_|\__,_|\___|_|  \___/|___/ */
/* ================================= */

//	ansi color escape codes
# define ANS_R		"\033[31m"
# define ANS_G		"\033[32m"
# define ANS_U		"\033[34m"
# define ANS_Y		"\033[33m"
# define ANS_C		"\033[36m"
# define ANS_M		"\033[35m"
# define ANS_W		"\033[37m"
# define ANS_RES	"\033[0m"

//	enviroment variables dictionary
# define KEY	0
# define VAL	1

//	cmd in-out
# define IN		0
# define OUT	1
# define ERR	2

//	pipes IO
# define PWRITE		0
# define PREAD		1

//	tokens
# define T_OPS		"|<->+"
# define T_QTS		"\"\'"

# define T_PIPE		0
# define T_IN 		1
# define T_HDOC		2
# define T_OUT		3
# define T_APP		4

# define T_QDOB		0
# define T_QSIN		1

/*  ____        __ _                  */
/* |  _ \  ___ / _(_)_ __   ___  ___  */
/* | | | |/ _ \ |_| | '_ \ / _ \/ __| */
/* | |_| |  __/  _| | | | |  __/\__ \ */
/* |____/ \___|_| |_|_| |_|\___||___/ */
/* ================================== */

typedef enum e_tokt
{
	// Symbols
	id_pipe,
	id_input,
	id_hdoc,
	id_output,
	id_append,
	// Quotes
	id_qdob,
	id_qsin,
	// Strings
	id_string,
	// Subshells
	id_pstart,
	id_pend,
	// Errors
	id_err_tok,
}	t_tokt;

// definir controles de estado?
// definir tipo de builtin?
// definir valores de error?
// definir definir señales?

/*  ____  _                   _        */
/* / ___|| |_ _ __ _   _  ___| |_ ___  */
/* \___ \| __| '__| | | |/ __| __/ __| */
/*  ___) | |_| |  | |_| | (__| |_\__ \ */
/* |____/ \__|_|   \__,_|\___|\__|___/ */
/* =================================== */

typedef struct s_env
{
	char			*dict[2];
	uint8_t			state;
}	t_env;

// seguro se necesita una similar para builtins
typedef struct s_cmd
{
	char			**args;		// [0] es command, **args termina en NULL
	ssize_t			io[2];		// o struct de fds con extra info?
	uint8_t			state;
}	t_cmd;

typedef struct s_tok
{
	t_tokt			type;
	size_t			pos;
	size_t			size;
}	t_tok;

typedef struct s_tok_ctrl
{
	//placeholder
	char			*input;		// si no se le agrega más que ctrl sea solo input
}	t_tok_ctrl;

typedef struct s_shell
{
	t_list			*env;
	t_list			*tokens;	// se podría agregar qenv o path a un ctrl
	t_env			*qenv[3];	// revisar, quizás se puede reformatear?
	ssize_t			bkstd[3];	// revisar bien cuando usarlo
	struct termios	termios;	// revisar bien para que darle uso
	// last command tokens
	// info / state
}	t_shell;

/*            ____            _        _                                      */
/*           |  _ \ _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___              */
/*           | |_) | '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __|             */
/*           |  __/| | | (_) | || (_) | |_| |_| | |_) |  __/\__ \             */
/*           |_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/             */
/*           ==============================|___/|_|==============             */

// program flow
void	verify(int ac, char **av);
bool	setup(t_shell *shell, char **env);
void	loop(t_shell *shell);

// env
bool	clone_env(t_shell *shell, char **env);
char	*get_env_val(t_list *list, char *key);
t_env	*get_env(t_list *list, char *key);
t_env	*line_to_dict_entry(char *line);
bool	line_to_env(t_shell *shell, char *line);
void	print_env(t_list *list);

// readline
bool	ft_readline(char **buff);

// builtins
int		echo(int argc, char **argv);

#endif
