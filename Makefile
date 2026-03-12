# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namatias <namatias@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 15:05:34 by namatias          #+#    #+#              #
#    Updated: 2026/03/11 22:22:22 by namatias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                       FLAGS AND VARIABLES TO COMPILE                         #
################################################################################

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

AST_DIR =		./ast/
SRC_DIR =		./src/
OBJ_DIR =		./obj/
SYNTAX_DIR =	./syntax/
INCLUDE_DIR =	./include/
EXEC_DIR =		./executer/
TOKEN_DIR =		./tokenize/
LIB_DIR =		./lib/libftx/

SYNTAX_FILES = 	syntax_check.c \
				syntax_utils.c \

EXEC_FILES = builtin/cd.c \
			 builtin/env.c \
			 builtin/pwd.c \
			 builtin/exit.c \
			 builtin/echo.c \
			 builtin/unset.c \
			 builtin/export.c \
			 builtin/builtin.c \
			 environment_list.c \
			 executions_utils.c \
			 expansion/expansion.c \
			 expansion/expansion_utils.c \
			 exec/pipe.c \
			 exec/redirect.c \
			 exec/executor.c \
			 exec/execute_ast.c \
			 exec/external_commands.c \
			 exec/external_commands_utils.c \
			 heredoc/heredocs.c \
			 heredoc/heredocs_utils.c \
			 signal/signal_set.c \
			 signal/signal_act.c \

TOKEN_FILES = token.c \
			  handlers.c \
			  token_utils.c \

AST_FILES =	cmd_arg.c \
			free_ast.c \
			cmd_redir.c \
 			ast_build.c \
			create_node.c \

SRC_FILES = main.c \
			cleaning.c \
			main_utils.c \
			$(addprefix $(AST_DIR), $(AST_FILES)) \
            $(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
			$(addprefix $(TOKEN_DIR), $(TOKEN_FILES)) \
			$(addprefix $(SYNTAX_DIR), $(SYNTAX_FILES)) \

FILES_O = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(FILES_O))
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

################################################################################
#                   	          LIBRARIES        		                       #
################################################################################

LIBFT = $(LIB_DIR)libft.a
IFLAGS = -I$(LIB_DIR)include
LDFLAGS = -L $(LIB_DIR) -lft -lreadline

INCLUDES = -I $(INCLUDE_DIR) -I $(LIB_DIR)include

################################################################################
#                                   COLORS                                     #
################################################################################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

################################################################################
#                          		   FUNCTIONS	                               #
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

val: all
	valgrind -q --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re val
