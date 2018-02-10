# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anyo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 15:43:40 by anyo              #+#    #+#              #
#    Updated: 2018/02/10 22:35:50 by gcadiou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = ./ft_memset	\
	   ./ft_bzero	\
	   ./ft_memcpy	\
	   ./ft_memccpy	\
	   ./ft_memmove	\
	   ./ft_memchr	\
	   ./ft_memcmp	\
	   ./ft_strlen	\
	   ./ft_strdup	\
	   ./ft_strcpy	\
	   ./ft_strncpy	\
	   ./ft_strcat	\
	   ./ft_strncat	\
	   ./ft_strlcat	\
	   ./ft_strchr	\
	   ./ft_strrchr	\
	   ./ft_strstr	\
	   ./ft_strnstr	\
	   ./ft_strcmp	\
	   ./ft_strncmp	\
	   ./ft_atoi	\
	   ./ft_isalpha	\
	   ./ft_isdigit	\
	   ./ft_isalnum	\
	   ./ft_isascii	\
	   ./ft_isprint	\
	   ./ft_toupper	\
	   ./ft_tolower	\
	   ./ft_memalloc	\
	   ./ft_memdel	\
	   ./ft_strnew	\
	   ./ft_strdel	\
	   ./ft_strclr	\
	   ./ft_striter	\
	   ./ft_striteri	\
	   ./ft_strmap	\
	   ./ft_strmapi	\
	   ./ft_strequ	\
	   ./ft_strnequ	\
	   ./ft_strsub	\
	   ./ft_strjoin	\
	   ./ft_strtrim	\
	   ./ft_strsplit	\
	   ./ft_itoa	\
	   ./ft_putchar	\
	   ./ft_putstr	\
	   ./ft_putendl	\
	   ./ft_putnbr	\
	   ./ft_putchar_fd	\
	   ./ft_putstr_fd	\
	   ./ft_putendl_fd	\
	   ./ft_putnbr_fd	\
	   ./ft_lstnew	\
	   ./ft_lstdelone	\
	   ./ft_lstdel	\
	   ./ft_lstadd	\
	   ./ft_lstiter	\
	   ./ft_lstmap	\
	   ./ft_nbofwords	\
	   ./ft_intlen	\
	   ./ft_check	\
	   ./ft_free	\
	   ./ft_putnbrnl	\
	   ./ft_putcharnl	\
	   ./ft_arrdup	\
	   ./ft_arrlen	\
	   ./ft_arrfree	\
	   ./ft_arrrev	\
	   ./ft_arrsort	\
	   ./ft_countc	\
	   ./ft_getch	\
	   ./ft_putarr	\
	   ./ft_putcolor	\
	   ./ft_strjoin_free	\
	   ./ft_strndup	\
	   ./ft_strnjoin	\
	   ./ft_strrcpy	\
	   ./ft_strrdup	\
	   ./ft_strcpy_until	\
	   ./ft_strlentil	\
	   ./ft_narrdup

H_SRC = ./
C_SRCS = $(addsuffix .c, $(SRCS))
O_SRCS = $(addsuffix .o, $(SRCS))

.PHONY: clean fclean re

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -I $(H_SRC) -c $(C_SRCS) 
	@ar rc $(NAME) $(O_SRCS)
	@ranlib $(NAME)

clean:
	@rm -f $(O_SRCS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
