# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 15:05:34 by namatias          #+#    #+#              #
#    Updated: 2026/01/21 18:00:22 by namatias         ###   ########.fr        #
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

PARSING_FILES = teste_parsing.c \

EXEC_FILES = teste_exec.c \

SRC_FILES = main.c \
			$(addprefix $(PARSING_DIR), $(PARSING_FILES)) \
            $(addprefix $(EXEC_DIR), $(EXEC_FILES))

FILES_O = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(FILES_O))
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

################################################################################
#                                    LIBRRIES                                  #
################################################################################

LIBFT = $(LIB_DIR)libft.a
IFLAGS = -I$(LIB_DIR)include
LDFLAGS = -L $(LIB_DIR) -lft -lreadline

INCLUDES = -I $(INCLUDE_DIR) -I $(LIB_DIR)include

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
