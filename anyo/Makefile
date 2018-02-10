# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apedron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 10:55:32 by apedron           #+#    #+#              #
#    Updated: 2018/02/08 15:11:52 by apedron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
LIB = -ltermcap
FLAGS = -Wall -Wextra -Werror

SRC_PATH = srcs/
INC_PATH = incs/
OBJ_PATH = objs/
LFT_PATH = libft/

SRC_FILES = cmd_execute.c		\
			cmd_init.c			\
			cmd_init_tools.c	\
			cmd_split.c			\
			cmd_tools.c			\
			env_init.c			\
			env_tools_1.c		\
			env_tools_2.c		\
			ft_isspace.c		\
			ft_strisblank.c		\
			get_window_size.c	\
			hist_tools.c		\
			input_get.c			\
			input_read.c		\
			kp_ccp.c			\
			kp_esc_fct.c		\
			kp_esc_opt_fct.c	\
			kp_fct.c			\
			main.c				\
			my_cd.c				\
			my_echo.c			\
			my_env.c			\
			my_exit.c			\
			my_setenv.c			\
			my_unsetenv.c		\
			sh_tools.c			\
			signal_handler.c	\
			term_mode.c			\
			token_fct.c			\
			tokenizer.c

INC_FILES = minishell.h	\
			macros.h
OBJ_FILES = $(SRC_FILES:.c=.o)
LFT_FILES = libft.a

INCS = $(addprefix $(INC_PATH), $(INC_FILES))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
LIBFT = $(addprefix $(LFT_PATH), $(LFT_FILES))

C_DBLUE = \033[38;5;074m
C_BRWN1 = \033[38;5;095m
C_GREEN = \033[38;5;114m
C_LBLUE = \033[38;5;117m
C_BRWN2 = \033[38;5;138m
C_PRED2 = \033[38;5;166m
C_PRED1 = \033[38;5;203m
C_RESET = \033[0m

DOT = \033[38;5;244m[*] \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC $(LFT_PATH) fclean && $(MAKE) -sC $(LFT_PATH)
	@echo "$(DOT)$(C_GREEN)Libft has been built.$(C_RESET)"
	@$(CC) $(FLAGS) $(LIB) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(DOT)$(C_DBLUE)Binary ./$(NAME) is $(C_LBLUE)ready$(C_RESET)$(C_DBLUE)!$(C_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS) Makefile
	@if [ ! -d "$(OBJ_PATH)" ]; then echo "$(DOT)$(C_BRWN2)Object files directory has been created.$(C_RESET)"; fi
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(DOT)$(C_BRWN1)Object file has been created...$(C_RESET)"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(DOT)$(C_PRED1)Object files directory has been deleted.$(C_RESET)"
	@$(MAKE) -sC $(LFT_PATH) clean
	@echo "$(DOT)$(C_PRED2)Libft has been cleaned: removed object files.$(C_RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(DOT)$(C_PRED1)Binary ./$(NAME) has been deleted.$(C_RESET)"
	@$(MAKE) -sC $(LFT_PATH) fclean
	@echo "$(DOT)$(C_PRED2)Libft has been cleaned: removed $(LIBFT).$(C_RESET)"

re: fclean all
