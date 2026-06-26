/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:11:35 by jgalizio          #+#    #+#             */
/*   Updated: 2026/06/26 10:46:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Z_MINISHELL_H
# define Z_MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
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

//  readline internal ignore markers
# define RL_START	"\001"
# define RL_END		"\002"

//	ansi color escape codes
# define ANS_R		"\001\033[31m\002"
# define ANS_G		"\001\033[32m\002"
# define ANS_U		"\001\033[34m\002"
# define ANS_Y		"\001\033[33m\002"
# define ANS_C		"\001\033[36m\002"
# define ANS_M		"\001\033[35m\002"
# define ANS_W		"\001\033[37m\002"
# define ANS_RES	"\001\033[0m\002"

//	enviroment variables dictionary
# define KEY	0
# define VAL	1

//	cmd in-out
# define IN		0
# define OUT	1
# define ERR	2

//	pipes IO
# define PWRITE		1
# define PREAD		0

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

//	Text and Errors
# define MS			"Minishell: "
# define E_MS		"ANS_R \"Minishell: \" ANS_RES"

# define E_DEBUG	"Incorrect argument passed, use -D for debug mode.\n"
# define E_ENV		"A correct set of environment variables must be provided.\n"
# define E_ARG		"Too many arguments passed\n"

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
	// Control
	id_space,
	id_fin
}	t_tokt;

extern int	g_sigexit;

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

typedef struct s_cmd
{
	ssize_t			io[2];
	t_list			*redirs;
	t_list			*args;
	char			**final_args;
	int				ac;
}	t_cmd;

typedef struct s_tok
{
	t_tokt			type;
	size_t			pos;
	size_t			size;
	uint8_t			state;
}	t_tok;

typedef struct s_redir
{
	t_tokt			redir_type;
	t_tok			target;
	char			*file_name;
}	t_redir;

typedef struct s_shell
{
	bool			is_active;
	bool			debug_mode;
	unsigned char	last_exit_code;
	int				pipe_count;
	ssize_t			bkstd[3];
	t_list			*env;
	t_list			*tokens;
	t_cmd			*cmds;
}	t_shell;

typedef int	(*t_builtin_fn)(int ac, char **av, t_shell *shell);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	func;
}	t_builtin;

/*            ____            _        _                                      */
/*           |  _ \ _ __ ___ | |_ ___ | |_ _   _ _ __   ___  ___              */
/*           | |_) | '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __|             */
/*           |  __/| | | (_) | || (_) | |_| |_| | |_) |  __/\__ \             */
/*           |_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/             */
/*           ==============================|___/|_|==============             */

// program flow
bool	setup(t_shell *shell, char **env);
void	loop(t_shell *shell);

// env
char	**env_list_to_ptr(t_list *env);
bool	clone_env(t_shell *shell, char **env);
char	*get_env_val(t_list *list, char *key);
void	detach_env(t_list *list, char *key);
t_env	*get_env(t_list *list, char *key);
t_env	*line_to_dict_entry(char *line);
bool	line_to_env(t_shell *shell, char *line);

void	print_env(t_list *list);
void	change_env_value(t_env *env, char *new_val, int update_state);
void	append_env_value(t_env *env, char *new_val, int update_state);
t_env	*create_dict_entry(char *key, char *val, int state);

// readline
bool	ft_readline(t_shell *shell, char **buff);

// signals
void	set_signal_parent(void);
void	set_signal_child(void);
void	set_signal_heredoc(void);
void 	set_signal_interactive(void);
void    set_signal(int signal, void (*sig_instruction)(int));
void    sig_heredoc(int sig);
void    sig_interactive(int sig);




//execution
char	*get_line_to_exec(char *key, t_list *env);
void	execution_pipeline(t_shell *shell, char *input);
pid_t   execute(t_cmd *cmd, t_shell *shell, int *prev_read_fd, int i);

//expansion
char	*expand(char *str, t_shell *shell);

//redirections
bool	handle_redirections(t_list *redirs);
char	*process_heredoc(char *delimiter, bool has_quotes, t_shell *shell);

// builtins
bool	is_builtin(char **av);
int	exec_builtin(int ac, char **av, t_shell *shell);
int		ft_pwd(int ac, char **av, t_shell* shell);
int		ft_echo(int ac, char **av, t_shell* shell);
int		ft_export(int ac, char **av, t_shell* shell);
void		entry_helper(int state, t_env *entry, char **data);
int		ft_cd(int ac, char **av, t_shell* shell);
int		ft_exit(int ac, char **av, t_shell* shell);
int		ft_env(int ac, char **av, t_shell* shell);
int 	ft_unset(int ac, char **av, t_shell *shell);

// tokenize
bool	tokenize(t_shell *shell, char *input);
void	__debug_tokens(t_list *token_list, char *input);
void	debug_tokens(t_list *token_list, char *input);
bool	token_syntax_checker(t_shell *shell, t_list *token_list, char *input);
bool	assemble_cmds(t_shell *shell);

// utils
void	put_char_range(char c, int len, char *color);
void	put_debug_indicator(char *input, int start, int len);
char	*token_to_string(t_tok *token, char *raw_line);
bool	is_expandable(t_tok *token, char *line);

bool	is_redir(t_tokt t);
bool	is_quoted(t_tokt t);

//cleanup
void	cleanup(t_shell *shell);
void	free_env_entry(void *env_entry);
void	heredoc_cleanup(t_shell *shell);
void	free_cmds(t_shell *shell);
void	child_cleanup(t_shell *shell);
void	cleanup_exit(t_shell *shell, int status);
void	child_error_cleaner(t_shell *shell, char **env, char *path, int i);

#endif
