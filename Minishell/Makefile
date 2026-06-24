# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 17:53:37 by jgalizio          #+#    #+#              #
#    Updated: 2025/07/02 13:16:32 by viaremko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc
CFLAGS			= -Wextra -Wall -Werror -g
#CFLAGS			+=-fsanitize=address -fno-omit-frame-pointer
RM				= rm -rf

LIBFT_DIR		= ./libft
BASE_DIR		= ./srcs_base
BONUS_DIR		= ./srcs_bonus
BUILD_DIR		= ./.build
BUILD_BONUS_DIR	= $(BUILD_DIR)/bonus
BUILD_BASE_DIR	= $(BUILD_DIR)/base

BASE_TARGET		= $(BUILD_BASE_DIR)/.base
BONUS_TARGET	= $(BUILD_BONUS_DIR)/.bonus
BASE_HEADERS	= $(BASE_DIR)/z_minishell.h
BONUS_HEADERS	= $(BONUS_DIR)/z_minishell_bonus.h
LIBFT_HEADERS	= $(LIBFT_DIR)/libft.h

HEADERS			= -I ./libft
BONUS_INC		= -I $(BONUS_DIR) $(HEADERS)

LIB_FLAGS		= -lreadline
LIBFT			= $(LIBFT_DIR)/libft.a
LIBS			= $(LIBFT) $(LIB_FLAGS)

BASE_SRCS		= $(addprefix $(BASE_DIR)/,	\
					a_main.c				\
					b_setup.c				\
					c_loop.c				\
					d_cleanup.c				\
					)

BASE_DIR_ENV = $(BASE_DIR)/env_lib
BASE_SRCS		+= $(addprefix $(BASE_DIR_ENV)/,				\
					create_env.c					\
					get_env.c						\
					detach_env.c						\
					modify_env.c					\
					print_env.c					\
					env_list_to_ptr.c	\
					)
						
BASE_DIR_SIG = $(BASE_DIR)/signals
BASE_SRCS		+= $(addprefix $(BASE_DIR_SIG)/,	\
					signals.c		\
					)

BASE_DIR_BUILTINS = $(BASE_DIR)/builtins
BASE_SRCS		+= $(addprefix $(BASE_DIR_BUILTINS)/,	\
				   	exec_builtin.c\
			   		ft_export.c	\
			   		ft_cd.c	\
					ft_pwd.c\
					ft_echo.c\
					ft_exit.c\
					ft_env.c\
					ft_unset.c\
					)

BASE_DIR_REDIR = $(BASE_DIR)/redirections
BASE_SRCS		+= $(addprefix $(BASE_DIR_REDIR)/,	\
					redirections.c	\
					heredoc.c	\
					)

BASE_DIR_RL = $(BASE_DIR)/readline
BASE_SRCS		+= $(addprefix $(BASE_DIR_RL)/,	\
					readline.c	\
					)

BASE_DIR_TOK = $(BASE_DIR)/tokenize
BASE_SRCS		+= $(addprefix $(BASE_DIR_TOK)/,	\
					a_tokenize.c					\
					b_interpreter.c					\
					c_assemble_cmds.c				\
					u_debug_tokens.c				\
					u_verifications.c				\
					)

BASE_DIR_UTILS = $(BASE_DIR)/utils
BASE_SRCS		+= $(addprefix $(BASE_DIR_UTILS)/,	\
					line_indicator.c	\
					token_utils.c 		\
					)

BASE_DIR_EXEC = $(BASE_DIR)/execution
BASE_SRCS		+= $(addprefix $(BASE_DIR_EXEC)/, 		\
				get_line_to_exec.c 		\
				execute.c			\
				)
BASE_DIR_EXPA = $(BASE_DIR)/expansion
BASE_SRCS		+= $(addprefix $(BASE_DIR_EXPA)/, 		\
				expansor.c			\
				)

BASE_DIR_CLEAN = $(BASE_DIR)/cleanup
BASE_SRCS		+= $(addprefix $(BASE_DIR_CLEAN)/, 		\
					cmds.c								\
					env.c								\
					heredoc.c							\
				)

BONUS_SRCS		= $(addprefix $(BONUS_DIR)/,	\
					)

BASE_OBJS		= $(BASE_SRCS:$(BASE_DIR)/%.c=$(BUILD_BASE_DIR)/%.o)
BONUS_OBJS		= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BUILD_BONUS_DIR)/%.o)

all: $(NAME)

$(NAME): $(BASE_TARGET)

# bonus: $(BONUS_TARGET)

$(BASE_TARGET): $(BASE_OBJS) $(LIBFT)
	@echo "Creating minishell..."
	@$(CC) $(CFLAGS) $(BASE_OBJS) $(BASE_INC) $(LIBS) -o $(NAME)
	@touch $(BASE_TARGET)
	@rm -f $(BONUS_TARGET)
	@echo "Done! :D"

$(BONUS_TARGET): $(BONUS_OBJS) $(LIBFT)
	@echo "Creating bonus..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(BONUS_INC) $(LIBS)-o $(NAME)
	@touch $(BONUS_TARGET)
	@rm -f $(BASE_TARGET)
	@echo "Done! :D"

$(BUILD_BASE_DIR)/%.o: $(BASE_DIR)/%.c $(BASE_HEADERS) $(LIBFT)
	@echo "compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(BASE_INC) -o $@

$(BUILD_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c $(BONUS_HEADERS) $(LIBFT)
	@echo "compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(BONUS_INC) -o $@

$(LIBFT): $(LIBFT_HEADERS)
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Done! :D"

clean:
	@echo "Cleaning objects..."
	@$(RM) $(BASE_OBJS) $(BONUS_OBJS) $(BASE_TARGET) $(BONUS_TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :D"

re: fclean all

v: re
	@valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=../readline.supp --trace-children=yes --track-fds=yes ./minishell


# rebonus: fclean bonus

#.PHONY: all clean bonus fclean re rebonus

.PHONY: all clean fclean re
