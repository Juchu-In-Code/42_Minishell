# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:08 by jgalizio          #+#    #+#              #
#    Updated: 2026/06/25 10:12:02 by jgalizio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
CFLAGS			= -Wall -Werror -Wextra -g -fPIE
AR				= ar crs
RM				= rm -rf

HEADER			= libft.h

BUILD_DIR		= ./.build

DIR_CHAR		= ./chars
DIR_ERROR		= ./error
DIR_IO			= ./io
DIR_LIST		= ./list
DIR_MEM			= ./memory
DIR_NUMS		= ./nums
DIR_STRINGS		= ./strings
DIR_UTILS		= ./utils

MODULES			= $(addprefix $(DIR_UTILS)/, \
			  		ft_get_array_length.c)

MODULES			+= $(addprefix $(DIR_CHAR)/,		\
					ft_isalnum.c				\
					ft_isalpha.c				\
					ft_isascii.c				\
					ft_isdigit.c				\
					ft_isprint.c				\
					ft_isspace.c				\
					ft_tolower.c				\
					ft_toupper.c				\
					)

MODULES			+= $(addprefix $(DIR_ERROR)/,	\
					error_utils.c				\
					)

MODULES			+= $(addprefix $(DIR_IO)/,		\
					ft_printf.c					\
					ft_putchar_fd.c				\
					ft_putendl_fd.c				\
					ft_puthex_fd.c				\
					ft_putmemaddr_fd.c			\
					ft_putnbr_fd.c				\
					ft_putstr_fd.c				\
					ft_putunbr_fd.c				\
					gnl_og.c					\
					)

MODULES			+= $(addprefix $(DIR_LIST)/,	\
					list_create.c				\
					list_free.c					\
					list_insert.c				\
					list_remove.c				\
					)

MODULES			+= $(addprefix $(DIR_MEM)/,		\
					ft_bzero.c					\
					ft_calloc.c					\
					ft_free.c					\
					ft_free_mtx.c				\
					ft_memchr.c					\
					ft_memcmp.c					\
					ft_memcpy.c					\
					ft_memmove.c				\
					ft_memset.c					\
					ft_realloc.c				\
					)

MODULES			+= $(addprefix $(DIR_NUMS)/,	\
					ft_atoi.c					\
					ft_atoi_hex.c				\
					ft_atol.c					\
					ft_numlen.c					\
					)

MODULES			+= $(addprefix $(DIR_STRINGS)/,	\
					ft_is_str_numeric.c			\
					ft_itoa.c					\
					ft_split.c					\
					ft_strchr.c					\
					ft_strchr_index.c			\
					ft_strcmp.c					\
					ft_count_arrays.c			\
					ft_print_matrix.c			\
					ft_strdup.c					\
					ft_str_isempty.c			\
					ft_striteri.c				\
					ft_strjoin.c				\
					ft_strjoinv.c				\
					ft_strjoinpp.c				\
					ft_strlcat.c				\
					ft_strlcpy.c				\
					ft_strlen.c					\
					ft_strlenv.c				\
					ft_strmapi.c				\
					ft_strncmp.c				\
					ft_strnstr.c				\
					ft_strrchr.c				\
					ft_strtrim.c				\
					ft_strunt.c					\
					ft_substr.c					\
					)

OBJS		=  $(MODULES:%.c=%.o)
DIR_OBJS	=  $(OBJS:%=$(BUILD_DIR)/%)

all: $(NAME)

$(NAME): $(DIR_OBJS)
	@echo "Creating $(NAME)..."
	@$(AR) $@ $^
	@echo "$(NAME) created successfully!"

$(BUILD_DIR)/%.o: %.c $(HEADER)
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	@$(RM) $(OBJS)
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :]"

re: fclean all

.PHONY: all clean fclean re
