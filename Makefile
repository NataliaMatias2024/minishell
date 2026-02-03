# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 15:05:34 by namatias          #+#    #+#              #
#    Updated: 2026/02/03 16:48:33 by namatias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                       FLAGS AND VARIABLES TO COMPILE                         #
################################################################################

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR =		./src/
OBJ_DIR =		./obj/
LIB_DIR =		./lib/libftx/
INCLUDE_DIR =	./include/
PARSING_DIR =	./parsing/
EXEC_DIR =		./execution/

PARSING_FILES =

EXEC_FILES = builtin/pwd.c \
			 builtin/exit.c \
			 builtin/cd.c \
			 builtin/builtin_utils.c \
			 environment_list.c  \
			 linked_list.c

SRC_FILES = main.c \
			$(addprefix $(PARSING_DIR), $(PARSING_FILES)) \
            $(addprefix $(EXEC_DIR), $(EXEC_FILES))

FILES_O = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(FILES_O))
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

################################################################################
#                                    LIBRRIES                                  #
################################################################################

# Caminho do Homebrew no WSL/Linux
READLINE_PATH = /home/linuxbrew/.linuxbrew

LIBFT = $(LIB_DIR)libft.a
IFLAGS = -I$(LIB_DIR)include -I$(READLINE_PATH)/include
LDFLAGS = -L$(LIB_DIR) -lft -L$(READLINE_PATH)/lib -lreadline

# Atualizando os INCLUDES para encontrar o readline/readline.h
INCLUDES = -I$(INCLUDE_DIR) -I$(LIB_DIR)include -I$(READLINE_PATH)/include

#LIBFT = $(LIB_DIR)libft.a
#IFLAGS = -I$(LIB_DIR)include
#LDFLAGS = -L $(LIB_DIR) -lft -lreadline

#INCLUDES = -I $(INCLUDE_DIR) -I $(LIB_DIR)include

################################################################################
#                                   Colors                                     #
################################################################################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

################################################################################
#                             Funções / Functions                              #
################################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) --silent

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) --silent

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR) --silent

re: fclean all

.PHONY: all clean fclean re
